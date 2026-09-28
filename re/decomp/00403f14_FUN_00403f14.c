// FUN_00403f14 @ 00403f14 size=72 sig=undefined FUN_00403f14() cc=unknown
// callers: 
// callees: FUN_00442900

undefined4 FUN_00403f14(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  
  puVar2 = &DAT_00645370;
  while( true ) {
    if ((undefined2 *)0x651caf < puVar2) {
      return 0;
    }
    if (((*(char *)(puVar2 + 3) != '\0') && (*(char *)(puVar2 + 4) == param_3)) &&
       (iVar1 = FUN_00442900(puVar2,param_1), param_2 == iVar1)) break;
    puVar2 = puVar2 + 0x2e;
  }
  return 1;
}

