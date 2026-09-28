// FUN_00460f68 @ 00460f68 size=58 sig=undefined FUN_00460f68() cc=unknown
// callers: FUN_00461078,FUN_00460fa4
// callees: 

void FUN_00460f68(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar2 = &DAT_00522594;
  do {
    iVar3 = 0;
    piVar1 = piVar2;
    do {
      if (*piVar1 != 0) {
        *piVar1 = (int)(&DAT_005a43d0 + *piVar1 * 0xadc);
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 0x31;
    } while (iVar3 < 0x32);
    iVar4 = iVar4 + 1;
    piVar2 = piVar2 + 0x992;
  } while (iVar4 < 7);
  return;
}

