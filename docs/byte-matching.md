# Byte matching reproducible

El sistema compara buffers de salida, no el código máquina compilado de las funciones.
Reutiliza CMake/CTest, `dl2save`, `save::Document`, `SessionRng` y el lector HDX de
`tools/savparse.py`. No ejecuta un turno ni activa una partida.

## Ejecutar en Windows

Desde la raíz, con las dependencias de compilación habituales:

```powershell
.\run-tests.ps1 --build-dir build-verified --data-dir "C:\GOG Games\Deadlock 2"
.\run-byte-matching.ps1 --build-dir build-verified --data-dir "C:\GOG Games\Deadlock 2" --require-originals --output results/current
.\generate-status.ps1 --results results/current/results.json
Start-Process results/current/results.html
```

Cada ejecución requiere un directorio de salida **nuevo**. Así no se mezclan diffs
ni salidas antiguas con resultados nuevos. Puede omitirse `--output` para obtener
un nombre UTC único dentro de `results/`. Los originales se leen únicamente.
`DL2_DATA` es la alternativa a `--data-dir`; no se adivina una instalación al ejecutar
byte matching. La compilación Windows conserva los valores por defecto de `build.ps1`.

Los comandos también son scripts Python portables:

```sh
python3 -B run-tests --build-dir build-ci
python3 -B run-byte-matching --build-dir build-ci --output results/current
python3 -B generate-status --results results/current/results.json
```

En Unix, configurar CMake previamente con SDL2 y `BUILD_TESTING=ON`. También pueden
invocarse `./run-tests`, `./run-byte-matching` y `./generate-status` con permiso de
ejecución. En PowerShell se usan los `.ps1` o `python -B <comando>`.

`run-tests` compila y ejecuta CTest, exporta JUnit y crea `status-ctest.json` en el
build. El recibo incluye huella del código/pruebas/manifests y hashes de los binarios.
Byte matching rechaza recibos ausentes, interrumpidos o caducados. Modificar fuentes
o recompilar después exige volver a ejecutar `run-tests`. Los hashes de fuentes
normalizan CRLF/LF para funcionar en Windows y Linux. Los hashes binarios no normalizan nada.

## Qué significa cada tasa

| Métrica | Numerador / denominador |
|---|---|
| CTest funcional | pruebas aprobadas / todas las pruebas CTest registradas, incluidas fallidas y omitidas |
| Byte Matching RAW | golden tests ejecutados con salida exactamente igual / todos los golden tests descubiertos, incluidos errores |
| Byte-level RAW | posiciones iguales / máximo de los dos tamaños, sumado sobre comparaciones realizadas |
| Byte Matching normalizado | casos exactamente iguales tras aplicar reglas / todos los golden tests descubiertos |
| Byte-level normalizado | posiciones iguales no excluidas / posiciones comparadas no excluidas |

Una salida extra o truncada cuenta como diferente en cada posición sin contraparte.
Nunca se divide por el tamaño mínimo. Se suman bytes antes de dividir; no se promedian
porcentajes de pruebas de diferente tamaño. Un denominador cero se publica como `null`
y se muestra `N/A`; dos buffers vacíos pueden ser iguales, pero no acreditan soporte.
Un proceso que falla, vence su timeout o no genera salida es ERROR, nunca una prueba
aprobada. Los bytes de una ejecución sin salida no se incluyen en la tasa de bytes:
se publica explícitamente el número de casos comparados y de errores, y el proceso
devuelve un código distinto de cero. Nunca interpretar la tasa de bytes aisladamente.

Los casos funcionales pueden pasar con una representación binaria distinta. CTest,
la terminación del adaptador y la igualdad binaria mantienen resultados independientes.

## Referencias y procedencia

Se distinguen tres clases tanto en JSON como en HTML:

- `original-artifact`: `TUTORIAL.SAV`, los archivos locales opcionales y las entradas
  de `LEVELS.HDX/HDD`. El resultado esperado es el archivo original sin cambios.
  El adaptador real ejecuta `dl2save roundtrip` sobre una copia del mismo input.
  Esto demuestra conservación del formato, **no ejecución equivalente de SaveGame**.
- `derived-oracle`: tres vectores fijos de ocho valores RNG, semilla 1, procedentes
  de las recurrencias documentadas y de los vectores independientes existentes en
  `test_session_rng.cpp`. `golden_probe` llama al `SessionRng` real y serializa cada
  valor como uint32 little-endian. No calcula sus valores esperados.
- `original-execution`: capturas obtenidas ejecutando un adaptador del original con
  el mismo input. La infraestructura está disponible; este repositorio no contiene
  un harness que ejecute funciones arbitrarias de `DEADLOCK.EXE`. No se presentan
  las otras clases como si fueran capturas de esa ejecución.

Sin instalación original, el conjunto `original-save-corpus` se marca SKIPPED con
el motivo. No se inventan su tamaño ni sus casos. `--require-originals` convierte
su ausencia en un fallo de CI. Si una baseline contenía sus casos, su desaparición
también es una regresión. Los golden locales comerciales se generan dentro del
directorio de resultados, excluido de Git. No hace falta distribuir esos datos.

## Contrato de un golden test

```text
tests/golden/rng-rand15/
    input.bin
    expected.bin
    metadata.json
```

Ejemplo de metadata para un adaptador propio (los hashes deben ser los reales):

```json
{
  "id": "my_case",
  "module": "my_module",
  "function": "my_function",
  "description": "Contrato concreto de la operación",
  "version": "original-build-id",
  "provenance": {"kind": "original-execution", "source": "original adapter"},
  "critical": true,
  "command": ["/absolute/path/to/port-adapter", "{input}", "{output}"],
  "input_sha256": "SHA-256 real de input.bin",
  "expected_sha256": "SHA-256 real de expected.bin"
}
```

`command` es un argv, sin shell. Los tokens disponibles son `{input}`, `{output}`,
`{cli}` (dl2save del build) y `{probe}` (golden_probe del build). Las llaves literales
se escapan como `{{` y `}}`. El directorio de trabajo es temporal y aislado; el input
se copia allí y se comprueba que no cambió. `timeout` opcional está en segundos (30
por defecto). Los metadatos son configuración ejecutable de confianza, igual que
los tests del repositorio. IDs duplicados, paths escapados y hashes alterados fallan.

Para capturar una referencia nueva:

```powershell
python -B tools/status.py capture-reference --input sample.bin --metadata case.json --reference-command '["C:/adapters/original.exe", "{input}", "{output}"]' --destination tests/golden/local/my_case
```

El adaptador original debe escribir bytes deterministas. `case.json` especifica la
descripción, versión y comando de la **reimplementación**. El capturador añade hashes,
proveniencia, argv original, hash del ejecutable y fecha UTC. Valida antes de publicar
y rechaza un destino existente. No actualiza referencias automáticamente al fallar
un test. Capturar con un ejecutable etiquetado como original exige que el responsable
aporte el original correcto; la herramienta registra esa procedencia, no la autentica.

## Normalización explícita

Dentro de `metadata.json`, opcionalmente:

```json
{"normalization": {"ignore": [{"offset": 32, "length": 8, "reason": "runtime pointer"}]}}
```

JSON utiliza enteros decimales (32 equivale a 0x20). Cada regla requiere offset,
longitud positiva y motivo. No se detectan ni ignoran automáticamente timestamps,
punteros, IDs, semillas ni relocaciones. Se rechazan rangos solapados, desconocidos,
negativos o que excedan cualquiera de los buffers. Los bytes excluidos no se suman
como iguales. Se calculan hashes normalizados sobre la concatenación ordenada de
los bytes restantes y se conservan además los hashes RAW. RAW nunca cambia por una regla.
Las reglas y el número de bytes excluidos están en el informe. La política crítica
de este proyecto exige RAW exacto: una normalización no convierte un fallo crítico
en éxito. Cambiar esa política requeriría una decisión explícita del proyecto.

## Artefactos y diagnóstico

```text
results/<run>/
    results.json
    results.html
    artifacts/<test_id>/
        input.bin
        expected.bin
        actual.bin
        metadata.json
        stdout.txt
        stderr.txt
    mismatches/<test_id>.diff
    mismatches/<test_id>.normalized.diff
    original-goldens/<test_id>/...
```

Cada registro contiene test ID, módulo, función, input/output enlazados, sus hashes,
tamaños, bytes iguales/diferentes/totales, porcentaje, timestamp UTC, versión original,
commit/build del port, hash del ejecutable, reglas y contrato. En error puede no existir
`actual.bin`; el campo correspondiente será `null`, acompañado del diagnóstico.
Los diffs de texto contienen **todos** los offsets diferentes; `--` indica ausencia.
JSON y el diff visual HTML muestran hasta 256 offsets por comparación y declaran
el truncamiento; el enlace al diff completo y los buffers permiten investigar el resto.

## Regresiones y CI

```powershell
.\run-byte-matching.ps1 --build-dir build-verified --output results/after --baseline results/before/results.json --data-dir "C:\GOG Games\Deadlock 2"
```

La comparación usa fracciones exactas, no porcentajes redondeados. Falla ante:

- golden crítico RAW distinto, error de ejecución o fallo de CTest;
- descenso de tasa RAW/normalizada por caso o agregada, o pérdida de igualdad exacta;
- caso eliminado/antes ejecutado y ahora omitido, contrato cambiado (input, referencia,
  normalización o metadata), pérdida de una prueba funcional previamente aprobada;
- instrucción GPU o función antes verificada que pierde evidencia, o catálogo reducido.

La eliminación de pruebas o el cambio de referencias no se trata como mejora. Una
actualización deliberada requiere revisar el nuevo contrato y elegir explícitamente
una nueva baseline. Sin `--baseline`, el informe declara que no se compararon regresiones.
No atribuye resultados a `HEAD^` si no se ejecutó esa versión.

`.github/workflows/status.yml` compila y ejecuta el commit base (base del PR o commit
anterior del push) en un worktree separado cuando ya dispone de esta infraestructura,
y después el commit actual. Guarda HTML/JSON/JUnit y diffs incluso al fallar. El primer
commit con la infraestructura declara baseline ausente. El CI público ejecuta vectores
redistribuibles y marca los datos comerciales ausentes; un entorno privado puede usar
`DL2_DATA` y `--require-originals`. El workflow queda configurado; su ejecución remota
requiere subir el repositorio a GitHub. Las marcas de tiempo y rutas de ejecución son
auditoría variable: mismos inputs/build/reglas producen los mismos bytes y métricas.

Si el commit base no compila o no puede generar un informe, el workflow conserva
`results/ci/baseline.log` y advierte que no pudo comparar regresiones. Esto permite
validar una corrección sobre una versión rota sin simular una baseline aprobada.
El commit actual sigue obligado a compilar y pasar las pruebas. Sus logs de
configuración, build/CTest y byte matching también se publican si falla antes de
generar JSON/HTML.

## Pruebas de la infraestructura

```powershell
python -B tests/test_status_metrics.py
```

Se ejecutan también como `status_metrics` dentro de CTest. Verifican conteo, tamaños,
hash SHA-256 conocido, vacíos, reglas, tasas ponderadas, ejecución real de adaptadores,
errores/timeouts, integridad de golden, diffs, evidencias, regresiones y escape HTML.
