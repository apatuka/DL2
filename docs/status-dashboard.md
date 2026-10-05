# Status dashboard

`tools/status.py` genera un HTML autónomo desde `results.json`, sin servidor, framework
web adicional ni dependencias Python externas. Se abre directamente en el navegador.
Datos, fuentes y tasas quedan en el JSON para auditar o integrar otra interfaz.
Comandos y formato de golden: [byte-matching.md](byte-matching.md).

## Arquitectura y fuentes

| Componente | Responsabilidad / fuente |
|---|---|
| `tools/status_metrics/core.py` | comparación pura, SHA-256, normalización, porcentajes y regresiones |
| `tools/status_metrics/runner.py` | ejecución de golden y validación del catálogo/evidencia |
| `tools/status.py` | build/CTest, corpus original, captura de referencia y CLI |
| `tools/status_metrics/report.py` y `dashboard.html` | página autónoma, treemaps, tasas y diff visual |
| `re/functions.jsonl` | conjunto completo de funciones originales conocidas, deduplicado por dirección |
| `re/modules/*.txt` | asignación de cada función a módulo original; `gp_globals.txt` no es un módulo de funciones |
| `metrics/evidence.json` | contratos revisados, hashes de código/tests y pruebas que acreditan funciones/instrucciones |
| `metrics/shaders.json` | catálogo explícito de GPU por ID, nombre y familia; no aplicable en DL2 actual |
| `tests/golden/` | entradas y referencias binarias independientes del ejecutable probado |
| CTest JUnit / `status-ctest.json` | resultados funcionales, omisiones y huella del build |

No se crea una segunda implementación de la simulación ni un sistema de logging en
el juego. El proyecto ya tiene hooks de depuración y eventos RNG; el runner registra
stdout/stderr y artefactos sin cambiar el comportamiento del port.

## System libraries

En DL2, esta sección representa **módulos/componentes originales**, incluyendo juego,
CYLib, SMenu y RTL Borland. No representa DLLs del sistema operativo ni cada target
CMake. Cada dirección del catálogo se cuenta una sola vez. Referencias duplicadas
entre módulos o desconocidas provocan error. Las funciones fuera de los mapas
existentes se agrupan como `unclassified`, manteniendo el denominador completo.

Por módulo y globalmente:

```text
pending = total_known_functions - verified_implementations
percentage = verified_implementations / total_known_functions * 100
```

La cifra es un **límite inferior de implementación acreditada**, no una estimación
de cuánto código está escrito. El inventario existente no incluye una certificación
función a función; los comentarios `orig:`, archivos fuente, enums y placeholders
no se convierten automáticamente en implementaciones. El manifiesto inicial acredita
las tres primitivas RNG con vectores independientes y la suite `session_rng`. El
resto requiere registrar y revisar su evidencia. El codec se verifica por su contrato
de conservación, pero no se atribuye a SaveGame/LoadGame completos del original.

Cada entrada de evidencia necesita:

1. ID original existente y un contrato concreto.
2. Archivos de implementación, cabeceras y pruebas relevantes con SHA-256 de texto
   normalizado a LF. Un cambio deja de acreditar automáticamente esa entrada.
3. Golden tests RAW exactos con bytes no vacíos, ejecutados en el informe actual.
4. Pruebas CTest funcionales aprobadas en el mismo código/build.

Las pruebas constituyen evidencia de los contratos y casos declarados, no una prueba
matemática de equivalencia universal. Los hashes obligan a revisar un cambio antes
de renovar la evidencia; no demuestran semántica por sí mismos. No actualizar hashes
como trámite para esconder una regresión. Tras revisar código, vectores y contratos,
se obtienen con `status_metrics.runner.text_hash(Path(...))`, importable desde `tools/`.

El JSON incluye `known_ids`, `verified_ids`, catálogo completo y razones de evidencia
caducada. El HTML expone la tabla completa de módulos incluso cuando los rectángulos
son demasiado pequeños para llevar texto.

## GPU shader instructions

DL2 reconstruye un juego con sprites/paletas y SDL2; no contiene un ISA de shaders
reimplementado. Por eso `applicable: false`, catálogo vacío y porcentaje `null`.
El dashboard muestra **No aplicable**, nunca 0% o 100% de una GPU inventada.

Si el proyecto incorpora un backend propio, declarar `applicable: true` y cargar
en `instructions` su inventario real, por ejemplo objetos con `id`, `name`, `family`.
Usar el ISA/decoder del proyecto como fuente y mantener todos los conocidos, incluidos
no soportados. Registrar evidencia por ID en `metrics/evidence.json` → `shaders`, con
la misma estructura/condiciones de las librerías. Cada instrucción debe tener casos
que ejerciten su semántica, comparando salida binaria con un oráculo independiente
o hardware/original. Un enum, dispatch o stub no acredita soporte. Se agrupan por
familia y se calcula `implemented / total`; la regresión detecta soporte retirado.

## Visualización

Los treemaps se calculan desde los conteos del JSON mediante partición binaria
proporcional al total de cada grupo. Dentro de cada rectángulo, la fracción verde
representa implementadas; gris representa pendientes. No se redondea una fracción
pequeña a un bloque completamente verde. El borde visual no modifica los datos.

Se muestran nombre, porcentaje y conteos cuando caben; el tooltip conserva toda la
información. La página adapta el layout al ancho, incluye leyenda y tabla accesible
de módulos. Los gráficos de barras separan casos exactos y bytes iguales. El selector
RAW/normalizado recalcula la vista desde los dos resultados ya registrados; nunca
ejecuta código ni cambia los artefactos.

La tabla se filtra por nombre/módulo y estado. Al inspeccionar una prueba se ven
hashes, procedencia, build, reglas, error y offsets hexadecimales. Los archivos
completos se enlazan junto a la vista limitada. Las referencias originales y los
oráculos derivados tienen resúmenes independientes, además del global.

Los datos se insertan como JSON escapado; etiquetas y resultados se escriben con
`textContent`. No hay requests externos, librerías CDN ni porcentajes codificados
en el HTML. `generate-status` vuelve a dibujar un informe histórico con su fecha y
build originales; no lo presenta como una nueva ejecución de las pruebas.
