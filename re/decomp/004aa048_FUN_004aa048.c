// FUN_004aa048 @ 004aa048 size=42 sig=undefined FUN_004aa048() cc=unknown
// callers: fopen
// callees: 

undefined4 * FUN_004aa048(void)

{
  undefined4 *puVar1;
  
  puVar1 = &DAT_0051fce4;
  while( true ) {
    if (*(char *)((int)puVar1 + 0x16) < '\0') {
      return puVar1;
    }
    if (&DAT_0051fce4 + DAT_00520194 * 6 <= puVar1) break;
    puVar1 = puVar1 + 6;
  }
  return (undefined4 *)0x0;
}

