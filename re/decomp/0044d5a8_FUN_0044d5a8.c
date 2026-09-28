// FUN_0044d5a8 @ 0044d5a8 size=86 sig=undefined FUN_0044d5a8() cc=unknown
// callers: 
// callees: FindConstructionSite

undefined4 * FUN_0044d5a8(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005a4eac;
  while( true ) {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar2) {
      return (undefined4 *)0x0;
    }
    if (((param_1 == *(char *)(puVar2 + 8)) && (*(short *)(puVar2 + 0xc) != 0)) &&
       (iVar1 = FindConstructionSite(puVar2,param_2), iVar1 != -1)) break;
    puVar2 = puVar2 + 0x2b7;
  }
  return puVar2;
}

