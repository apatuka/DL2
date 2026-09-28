# Tablas estáticas recuperadas

`tools/extract_tables.py` lee `DEADLOCK.EXE` con `pefile` y genera `data/tables.json` y
`src/game/data_tables.{h,cpp}`. La salida tipada está en `dl2::data`. Las direcciones y funciones
consumidoras están anotadas en el extractor y en la cabecera; son referencias al ejecutable local
v1.20 analizado en Ghidra. No son offsets de un ejecutable arbitrario de otra versión.

## Inventario principal

| Tabla | Dirección original | Registros |
|---|---|---:|
| Tipos de edificios | `0x4F9DBC` | 48, paso `0x32` |
| Costes de edificios | `0x4FA71C` | 48 × 11 materiales |
| Tipos de unidades | `0x4FAF7C` | 39, paso `0x24` |
| Costes de unidades | `0x4FB4F8` | 39 × 11 materiales |
| Tecnologías | `0x4FBBAC` | 48, paso `0x32` |
| Modificadores raciales | `0x4FC50C` | 64 × 8 valores `int16` |
| Producción por trabajo | `0x4F9BC4` | 11 × 11 valores `int32` |
| Tipos de eventos | `0x4FC90C` | 156 válidos; el siguiente registro ya no es un evento |
| Campañas | `0x4C6194` | 43, paso `0xD8` |
| Llegadas IA | `0x4DC434` | 10, paso `0x9C` |
| Ofertas Skirineen | `0x4C42F8` | 25, paso `0x0E` |

Las 51 agrupaciones extraídas incluyen también impuestos, población, costes de movimiento,
opciones de mundo, personalidad/ministros IA y cadenas de nombres. `data/tables.json` conserva
el mapa completo `addresses` y sus valores bajo `tables`.

Los punteros a rutinas del original se representan como `OrigFunction { addr, name }`:
identifican qué falta portar, pero no son funciones ejecutables del nuevo juego.
Los estados mutables de tecnologías, campañas y relaciones deben inicializarse en la lógica;
el hecho de disponer de las tablas estáticas no implementa esos sistemas.

## Verificación sin modificar archivos

```powershell
py -3 -B tests/test_game_data.py tables "C:\GOG Games\Deadlock 2"
```

Esta prueba vuelve a extraer en memoria, ejecuta los controles de coherencia del extractor y
compara las 51 agrupaciones con el JSON y el C++ generado. En la recuperación del 27/09/2026
pasó con cero diferencias. No prueba aún el comportamiento de economía, IA ni combate.
Se registra también como `original_tables` en CTest si hay Python; sin datos o `pefile` se
informa como omitida, nunca como una validación realizada.

`extract_tables.py` es el **generador**, no el verificador: al ejecutarlo sobrescribe los tres
archivos generados. Cambiar el extractor y revisar su diff es preferible a editar a mano la salida.

## Integración pendiente

Claude dejó otras representaciones de estas tablas en `economy_tables.cpp` y declaraciones
adicionales en `turn_api.h`. Todavía no están integradas. Antes de enlazar economía/cargador/turnos,
hay que contrastar layouts, índices y valores, y elegir adaptadores a una fuente común. No asumir
que las copias tienen el mismo significado por compartir dirección o un nombre similar.

El generador temporal de economía quedó sobrescrito por otro agente. El historial original
conserva su contenido; ver [RECOVERY.md](RECOVERY.md). No regenerar `economy_tables.cpp` con el
`gen_tables.py` que quedó en el directorio temporal.
