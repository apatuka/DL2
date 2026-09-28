// FUN_0040fe58 @ 0040fe58 size=98 sig=undefined FUN_0040fe58() cc=unknown
// callers: FUN_0040febc
// callees: FUN_0040da38,FUN_0040d808,FUN_0040d64c

int FUN_0040fe58(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar3) {
      return -1;
    }
    if (*(char *)((int)puVar3 + 0x7e) != '\0') {
      uVar1 = FUN_0040da38(param_1);
      iVar2 = FUN_0040d64c(param_1,puVar3,uVar1);
      if ((iVar2 != 0) &&
         (iVar2 = FUN_0040d808(param_1,puVar3,*(undefined4 *)(param_1 + 0x10)), iVar2 != 0)) {
        return (int)*(short *)((int)puVar3 + 0x1a);
      }
    }
    puVar3 = puVar3 + 0x2b7;
  } while( true );
}

