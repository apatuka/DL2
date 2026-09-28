// FUN_00409f6c @ 00409f6c size=298 sig=undefined FUN_00409f6c() cc=unknown
// callers: FUN_0040a098
// callees: FUN_0040a524,FUN_0044d034,FUN_0046b0e4,FUN_00407d60,FUN_00409d68,FUN_0046b074,FUN_0046ca40

void FUN_00409f6c(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  undefined4 local_c;
  
  iVar8 = 0;
  bVar2 = true;
  piVar7 = &DAT_00521bb4;
  do {
    iVar6 = *piVar7;
    if ((*(char *)(iVar6 + 0x21) != '\0') && (*(short *)(iVar6 + 0x30) != 0)) {
      local_c = 100;
      iVar3 = FUN_0044d034(iVar6,0x11);
      sVar1 = *(short *)(&DAT_00559f50 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2);
      iVar4 = FUN_0046b0e4(iVar6);
      if ((iVar4 * 9) / 10 <= (int)*(short *)(iVar6 + 0x30)) {
        local_c = 100000;
      }
      iVar4 = FUN_0046b074(iVar6);
      if (iVar3 * sVar1 * 0xf < iVar4) {
        uVar5 = FUN_0046b0e4(iVar6);
        iVar3 = (int)uVar5 >> 1;
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar5 & 1) != 0);
        }
        if (iVar3 < *(short *)(iVar6 + 0x30)) {
          FUN_00407d60(param_1,5,local_c,1,(int)*(short *)(iVar6 + 0x1a),0x14,1);
        }
      }
      iVar8 = iVar8 + 1;
    }
    iVar6 = FUN_00409d68(iVar6);
    if (iVar6 == 0) {
      bVar2 = false;
    }
    piVar7 = (int *)piVar7[1];
  } while (piVar7 != &DAT_00521bb4);
  if (!bVar2) {
    if (1 < iVar8) {
      return;
    }
    uVar5 = FUN_0046ca40();
    if ((uVar5 & 3) != 0) {
      return;
    }
  }
  FUN_0040a524(param_1,(int)(char)(&DAT_0059f381)[param_1 * 0x2d8],0);
  return;
}

