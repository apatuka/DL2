// FUN_00407ad8 @ 00407ad8 size=271 sig=undefined FUN_00407ad8() cc=unknown
// callers: FUN_00407be8
// callees: FUN_00476cc0,FUN_0046ca40,FUN_0046bdfc,FUN_00407864

void FUN_00407ad8(int param_1,int param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_8;
  
  if (0 < param_3) {
    uVar3 = FUN_0046ca40();
    if (((uVar3 & 7) == 0) && (iVar4 = FUN_00407864(param_1,param_2,param_3), iVar4 != 0)) {
      return;
    }
    iVar4 = 0;
    local_8 = 0;
    bVar2 = false;
    piVar6 = &DAT_00521bb4;
    do {
      iVar1 = *piVar6;
      iVar5 = FUN_0046bdfc(iVar1);
      if ((((*(short *)(iVar1 + 0x9c2) != 0) ||
           (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0)) &&
          (0x4f < iVar5)) && (local_8 < *(int *)(iVar1 + 0x3a + param_2 * 4))) {
        local_8 = *(int *)(iVar1 + 0x3a + param_2 * 4);
        iVar4 = iVar1;
      }
      if (iVar5 < 0x50) {
        bVar2 = true;
      }
      piVar6 = (int *)piVar6[1];
    } while (piVar6 != &DAT_00521bb4);
    if ((iVar4 != 0) && (!bVar2)) {
      if (local_8 < param_3) {
        piVar6 = &local_8;
      }
      else {
        piVar6 = &param_3;
      }
      local_8 = *piVar6;
      FUN_00476cc0(&DAT_0059f160 + param_1 * 0x2d8,param_2,-local_8,(int)*(short *)(iVar4 + 0x1a));
    }
  }
  return;
}

