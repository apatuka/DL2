// FUN_004057c4 @ 004057c4 size=55 sig=undefined FUN_004057c4() cc=unknown
// callers: FUN_004018d8
// callees: FUN_00405798,FUN_00405760

void FUN_004057c4(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = &DAT_00522280;
  do {
    if (*piVar2 == 1) {
      iVar1 = piVar2[5];
      while (iVar1 != 0) {
        FUN_00405760(iVar1);
        iVar1 = piVar2[5];
      }
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 0x11;
  } while (iVar3 < 7);
  FUN_00405798();
  return;
}

