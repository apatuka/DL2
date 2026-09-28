// FUN_004522c0 @ 004522c0 size=6 sig=undefined FUN_004522c0() cc=unknown
// callers: FUN_004566c4,FUN_004568c8
// callees: 

void FUN_004522c0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  int unaff_ESI;
  undefined1 auStack_74 [6];
  undefined1 uStack_6e;
  undefined1 uStack_6c;
  undefined1 uStack_50;
  undefined1 uStack_4e;
  undefined2 uStack_4c;
  undefined2 uStack_48;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  int iStack_c;
  int iStack_8;
  
  memset(auStack_74,0,0x5c);
  uStack_6c = *(undefined1 *)(DAT_0057cdf8 + 8);
  uStack_6e = 0x17;
  uStack_50 = 0;
  uStack_4e = 100;
  uStack_4c = 0;
  uStack_48 = 0;
  iStack_8 = 0;
  if (param_1 != (undefined4 *)0x0) {
    unaff_ESI = *(int *)((int)param_1 + 6);
    unaff_EBX = *(int *)((int)param_1 + 10);
    iStack_8 = FUN_0044ba18(*param_1);
  }
  if (iStack_8 != 0) {
    iVar2 = FUN_004511d8(unaff_ESI,unaff_EBX);
    if (iVar2 == 0) {
      iVar2 = FUN_00451b68(auStack_74);
      if (iVar2 != 0) {
        *(int *)(iVar2 + 0x28) = unaff_ESI;
        *(int *)(iVar2 + 0xc) = unaff_ESI;
        *(int *)(iVar2 + 0x20) = unaff_ESI;
        *(int *)(iVar2 + 0x2c) = unaff_EBX;
        *(int *)(iVar2 + 0x10) = unaff_EBX;
        *(int *)(iVar2 + 0x24) = unaff_EBX;
        FUN_004512d4(unaff_ESI,unaff_EBX);
      }
      iStack_8 = iStack_8 + -1;
      if (iStack_8 == 0) {
        return;
      }
    }
    iStack_c = 0x24;
    uStack_10 = 1;
    do {
      iVar2 = -1;
      if ((uStack_10 & 1) == 0) {
        iVar2 = 1;
      }
      if ((unaff_ESI < 0) || (uVar1 = uStack_10, 0x11 < unaff_ESI)) {
        unaff_EBX = unaff_EBX + uStack_10 * iVar2;
      }
      else {
        while (uStack_14 = uVar1, 0 < (int)uStack_14) {
          unaff_EBX = unaff_EBX + iVar2;
          if (((-1 < unaff_EBX) && (unaff_EBX < 0x12)) &&
             (iVar3 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar3 == 0)) {
            iVar3 = FUN_00451b68(auStack_74);
            if (iVar3 != 0) {
              *(int *)(iVar3 + 0x28) = unaff_ESI;
              *(int *)(iVar3 + 0xc) = unaff_ESI;
              *(int *)(iVar3 + 0x20) = unaff_ESI;
              *(int *)(iVar3 + 0x2c) = unaff_EBX;
              *(int *)(iVar3 + 0x10) = unaff_EBX;
              *(int *)(iVar3 + 0x24) = unaff_EBX;
              FUN_004512d4(unaff_ESI,unaff_EBX);
            }
            iStack_8 = iStack_8 + -1;
            if (iStack_8 == 0) {
              return;
            }
          }
          uVar1 = uStack_14 - 1;
        }
      }
      if ((unaff_EBX < 0) || (uVar1 = uStack_10, 0x11 < unaff_EBX)) {
        unaff_ESI = unaff_ESI + uStack_10 * iVar2;
      }
      else {
        while (uStack_18 = uVar1, 0 < (int)uStack_18) {
          unaff_ESI = unaff_ESI + iVar2;
          if (((-1 < unaff_ESI) && (unaff_ESI < 0x12)) &&
             (iVar3 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar3 == 0)) {
            iVar3 = FUN_00451b68(auStack_74);
            if (iVar3 != 0) {
              *(int *)(iVar3 + 0x28) = unaff_ESI;
              *(int *)(iVar3 + 0xc) = unaff_ESI;
              *(int *)(iVar3 + 0x20) = unaff_ESI;
              *(int *)(iVar3 + 0x2c) = unaff_EBX;
              *(int *)(iVar3 + 0x10) = unaff_EBX;
              *(int *)(iVar3 + 0x24) = unaff_EBX;
              FUN_004512d4(unaff_ESI,unaff_EBX);
            }
            iStack_8 = iStack_8 + -1;
            if (iStack_8 == 0) {
              return;
            }
          }
          uVar1 = uStack_18 - 1;
        }
      }
      uStack_10 = uStack_10 + 1;
    } while ((int)uStack_10 < iStack_c);
    if (unaff_ESI < 0x12) {
      for (; 0 < iStack_c; iStack_c = iStack_c + -1) {
        unaff_EBX = unaff_EBX + -1;
        if (((-1 < unaff_EBX) && (unaff_EBX < 0x12)) &&
           (iVar2 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar2 == 0)) {
          iVar2 = FUN_00451b68(auStack_74);
          if (iVar2 != 0) {
            *(int *)(iVar2 + 0x28) = unaff_ESI;
            *(int *)(iVar2 + 0xc) = unaff_ESI;
            *(int *)(iVar2 + 0x20) = unaff_ESI;
            *(int *)(iVar2 + 0x2c) = unaff_EBX;
            *(int *)(iVar2 + 0x10) = unaff_EBX;
            *(int *)(iVar2 + 0x24) = unaff_EBX;
            FUN_004512d4(unaff_ESI,unaff_EBX);
          }
          iStack_8 = iStack_8 + -1;
          if (iStack_8 == 0) {
            return;
          }
        }
      }
    }
  }
  return;
}

