# Continuación de ofertas humanas — CX-02

Reconstrucción desde análisis estático del 2026-10-05; no se ejecutó una
oferta en el juego original. Implementada en `ai_event_transaction.h/.cpp`
y en `State::beginAiEvent/answerAiOffer`. Fuentes: exportaciones históricas `00406dd8`,
`00476b8c`, `00476c44`, `00441700`, y ensamblado nuevo en
[`re/evidence/cx02-human-2026-10-05`](../re/evidence/cx02-human-2026-10-05).

## Secuencia que hay que conservar

1. La IA selecciona los términos, se pone en estado2 y escribe el turno de
   propuesta. Después comprueba si el destinatario está ocupado; una oferta
   a sí misma resulta ocupada por este mismo orden.
2. Si el humano está libre, `00476b8c` pone también al destinatario en estado2.
   Al crear correctamente el diálogo, `0042d0ac` elige un retrato de categoría15
   mediante **un Secondary15**, antes de recibir la respuesta. Las siete listas
   de categoría15 están recuperadas y se contrastan con el PE instalado.
3. `0042d304` admite aceptar (`0x25`) o rechazar (`0x26`). El original distingue
   fallos de creación/presentación: no se debe interpretar la ausencia de una
   ventana nueva como rechazo del usuario.
4. La respuesta pone al emisor en estado3/4 y al destinatario en0. No llama a
   la evaluación de respuesta IA, no añade su máscara de ofertas procesadas,
   ni consume el azar de rechazo IA ni concede su modificación de actitud+4.
5. Al aceptar, `00441700` rompe pactos incompatibles, notifica0x73, aplica las
   cuatro máscaras y notifica0x72 mientras el emisor sigue en3. Sólo después
   se intenta actitud+8 y el emisor vuelve a0. Rechazar intenta actitud−8.
   Un ACK de pacto denegado por alianzas deshabilitadas no cambia ese orden.
6. Debe continuar la operación exterior: segunda dirección del evento, siguiente
   destinatario, ruptura, guerra u otra negociación. Puede aparecer otra oferta
   humana antes de terminar la primera operación exterior.

## Contrato implementado

Un registro aislado `{emisor,destinatario,máscara}` y un booleano de aceptación
no bastan para reanudar. La operación pendiente necesita poseer su documento,
bindings IA, continuación de RNG/máscaras/cola y punto exacto de ejecución.
La interfaz devuelve `Completed` o `AwaitingHuman`, un identificador de
oferta y los términos/retrato; después aceptar una decisión para ese identificador.
Una oferta pendiente no es un turno terminado ni un SAV exportable.

`AiEventTransaction` posee una base inmutable y repite determinísticamente la
operación en privado usando su historial validado de respuestas. Cada repetición
comprueba identidad y checkpoint completo de las ofertas previas. No ejecuta
callbacks externos ni presentación; publica una sola ejecución lógica de los
efectos y del RNG. Las copias comparten snapshots inmutables: responder en una
copia no modifica la transacción original.

Se rechazan respuestas duplicadas, ofertas antiguas o checkpoints alterados.
`State` conserva documento, handles y RNG publicados mientras espera, bloquea
ediciones, preparación y captura, y sólo publica el evento completo tras validar
el grafo final. Una respuesta que falla conserva la oferta pendiente. El informe
pendiente describe el checkpoint privado; no sustituye el contexto publicado.
No se sustituye la respuesta humana por la cola ordinaria de mensajes IA.
El perfil admitido es offline y representa presentación exitosa del diálogo,
sin llegadas de red durante la espera. Hay un límite explícito de128 respuestas
por transacción y64 eventos recursivos; excederlos es un error atómico.

## Objetivos de campaña

Si participa el jugador local, el flag vivo de objetivo1 está activo y la
máscara es **exactamente2 o exactamente16**, `00441700` escribe1 en el primer
objetivo canónico de tipo1, antes de los callbacks. Son flags y tres valores
int32 vivos; los bytes del SAV no sustituyen ese contexto. Deben compartir
propiedad con los objetivos ya usados por demolición, investigación y economía.
Flag activo sin objetivo canónico correspondiente se rechaza por acceso nativo
fuera de dominio, como ya sucede con el objetivo12 de santuarios.

## Conciliación de pactos reanudable

`00441400` concilia los pactos en orden de filas y columnas, emite el evento58
al afectado y después0x73 a las terceras IA antes de intersectar las máscaras
vivas y copiar ambas referencias anteriores. No reinicia máscaras IA ni sustituye
los pasos anteriores del turno. Sus callbacks pueden alcanzar una oferta humana.
La función directa `reconcileAiPacts` conserva el rechazo atómico en ese caso.

`AiPactReconciliationTransaction` añade la continuación completa de ese recorrido.
Posee un cursor de fila/columna/fase/destinatario y conserva el XOR y los cuatro
valores anteriores capturados antes de cada entrega. Cada reacción IA usa su
propia `AiEventTransaction`; al completarla continúa con los destinatarios y
pares restantes, sin volver a emitir el log humano ni repetir los efectos previos.
La intersección siempre lee las máscaras modificadas por los callbacks.

Durante una espera, el informe contiene sólo los pares cuya intersección terminó;
su última entrega incluye la reacción parcial y el contexto AI/RNG de la oferta.
Al responder sustituye ese sufijo por la ejecución lógica del hijo. La oferta
sigue usando identidad/checkpoint exactos; cada entrega nueva recibe identidad
distinta, aunque sus ordinales empiecen de nuevo. No se expone el documento
incompleto. Una respuesta que falla conserva también el cursor y el log privados.

`State::beginAiPactReconciliation/answerAiPactOffer` comparten la exclusión de
ediciones y el acceso `pendingAiOffer()` con los eventos individuales. Publican
documento, RNG, AI, log, ciudades y campaña juntos al completar el recorrido.
Los nuevos comienzos deben continuar exactamente los contextos ya poseídos por
el estado. Esta operación todavía no programa el turno completo.

El orden importa: una ruptura secreta hecha por el jugador de índice mayor
puede quedar conciliada al visitar antes el par inverso, sin producir denuncia.
No se debe precomputar una lista de diferencias ni emitir un aviso adicional.
