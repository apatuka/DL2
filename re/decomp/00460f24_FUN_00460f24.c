// FUN_00460f24 @ 00460f24 size=67 sig=undefined FUN_00460f24() cc=unknown
// callers: FUN_00460fa4
// callees: 

void FUN_00460f24(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar3 = &DAT_00522594;
  do {
    iVar2 = 0;
    piVar1 = piVar3;
    do {
      if (*piVar1 != 0) {
        *piVar1 = (*piVar1 + -0x5a43d0) / 0xadc;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 0x31;
    } while (iVar2 < 0x32);
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 0x992;
  } while (iVar4 < 7);
  return;
}

