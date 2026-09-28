// FUN_004b0e5c @ 004b0e5c size=108 sig=undefined FUN_004b0e5c() cc=unknown
// callers: 
// callees: FUN_004b1180,FUN_004b11a4

void FUN_004b0e5c(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  
  piVar1 = DAT_005211ec;
  if (DAT_00521210 != 0) {
    while (piVar5 = piVar1, piVar5 != (int *)0x0) {
      piVar1 = (int *)piVar5[0x23];
      piVar5[2] = piVar5[2] + -1;
      iVar7 = piVar5[2];
      piVar6 = piVar5 + iVar7 + 3;
      for (; -1 < iVar7; iVar7 = iVar7 + -1) {
        iVar2 = *piVar6;
        iVar3 = *piVar5;
        iVar4 = *piVar6;
        piVar5[1] = iVar4 - (int)piVar5;
        *piVar5 = iVar4 - (int)piVar5;
        FUN_004b1180(iVar2,iVar3 - (iVar2 - (int)piVar5));
        FUN_004b11a4(iVar2);
        piVar6 = piVar6 + -1;
      }
    }
  }
  return;
}

