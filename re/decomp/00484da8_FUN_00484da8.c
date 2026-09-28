// FUN_00484da8 @ 00484da8 size=124 sig=undefined FUN_00484da8() cc=unknown
// callers: FUN_004609e8,FUN_0047c128,FUN_0044df94
// callees: FUN_004b02a8,FUN_00484bf0

void FUN_00484da8(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 uVar5;
  
  iVar3 = *param_1;
  if (iVar3 == 0) {
    uVar5 = 0x34;
    iVar3 = FUN_004b02a8(0x34);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar4 = 0xb;
      do {
        iVar2 = iVar4 * 4;
        iVar4 = iVar4 + -1;
      } while (-1 < iVar4);
      iVar3 = FUN_00484bf0(iVar3,uVar5,*(undefined4 *)(param_2 + iVar2),unaff_ESI,unaff_EBX,
                           unaff_EBP);
    }
    *param_1 = iVar3;
  }
  else {
    iVar4 = *(int *)(iVar3 + 0x30);
    iVar2 = iVar3;
    while (iVar1 = iVar3, iVar4 != 0) {
      iVar4 = *(int *)(iVar1 + 0x30);
      iVar3 = iVar4;
      iVar2 = iVar1;
    }
    uVar5 = 0x34;
    iVar3 = FUN_004b02a8(0x34);
    if (iVar3 == 0) {
      uVar5 = 0;
    }
    else {
      iVar4 = 0xb;
      do {
        iVar1 = iVar4 * 4;
        iVar4 = iVar4 + -1;
      } while (-1 < iVar4);
      uVar5 = FUN_00484bf0(iVar3,uVar5,*(undefined4 *)(param_2 + iVar1),unaff_ESI,unaff_EBX,
                           unaff_EBP);
    }
    *(undefined4 *)(iVar2 + 0x30) = uVar5;
  }
  return;
}

