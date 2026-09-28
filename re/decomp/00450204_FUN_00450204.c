// FUN_00450204 @ 00450204 size=282 sig=undefined FUN_00450204() cc=unknown
// callers: FUN_00415924,FUN_00486e34,FUN_00450380
// callees: FUN_0044fdf0,FUN_0044fe1c

undefined4 FUN_00450204(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = FUN_0044fe1c(param_1);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_0044fdf0(param_1);
    iVar6 = iVar1 * 0x44 + DAT_004d5a94 * 0xd8;
    iVar1 = FUN_0044fdf0(param_1);
    iVar7 = 0;
    piVar3 = (int *)(&DAT_004c61e0 + iVar1 * 0x44 + DAT_004d5a94 * 0xd8);
    if (param_1 == 0xd) {
      puVar4 = &DAT_005a4eac;
      for (iVar1 = 1; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
        if ((*(char *)(puVar4 + 8) == DAT_0058f1f4) && (*(char *)((int)puVar4 + 0x21) == '\0')) {
          iVar7 = iVar7 + 1;
        }
        puVar4 = puVar4 + 0x2b7;
      }
    }
    else {
      piVar5 = (int *)(&DAT_004c61ac + iVar6);
      for (iVar1 = 2; iVar1 < *(int *)(&DAT_004c61a8 + iVar6) + 2; iVar1 = iVar1 + 1) {
        if ((char)(&DAT_005a43f0)[*piVar5 * 0xadc] == DAT_0058f1f4) {
          iVar7 = iVar7 + 1;
        }
        piVar5 = piVar5 + 1;
      }
    }
    if (iVar7 < *(int *)(&DAT_004c61a8 + iVar6)) {
      *piVar3 = 0;
    }
    else if (*piVar3 == 0) {
      *piVar3 = DAT_0059f154;
    }
    if ((*piVar3 == 0) || (DAT_0059f154 - *piVar3 < *(int *)(&DAT_004c61a4 + iVar6))) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

