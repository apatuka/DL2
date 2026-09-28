// FUN_004522c6 @ 004522c6 size=522 sig=undefined FUN_004522c6() cc=unknown
// callers: 
// callees: FUN_00451b68,FUN_004511d8,memset,FUN_0044ba18,FUN_004512d4

void FUN_004522c6(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  
  puVar2 = *(undefined4 **)(unaff_EBP + 8);
  memset(unaff_EBP + -0x70,0,0x5c);
  *(undefined1 *)(unaff_EBP + -0x68) = *(undefined1 *)(DAT_0057cdf8 + 8);
  *(undefined1 *)(unaff_EBP + -0x6a) = 0x17;
  *(undefined1 *)(unaff_EBP + -0x4c) = 0;
  *(undefined1 *)(unaff_EBP + -0x4a) = 100;
  *(undefined2 *)(unaff_EBP + -0x48) = 0;
  *(undefined2 *)(unaff_EBP + -0x44) = 0;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if (puVar2 != (undefined4 *)0x0) {
    unaff_ESI = *(int *)((int)puVar2 + 6);
    unaff_EBX = *(int *)((int)puVar2 + 10);
    uVar3 = FUN_0044ba18(*puVar2);
    *(undefined4 *)(unaff_EBP + -4) = uVar3;
  }
  if (*(int *)(unaff_EBP + -4) != 0) {
    iVar4 = FUN_004511d8(unaff_ESI,unaff_EBX);
    if (iVar4 == 0) {
      iVar4 = FUN_00451b68(unaff_EBP + -0x70);
      if (iVar4 != 0) {
        *(int *)(iVar4 + 0x28) = unaff_ESI;
        *(int *)(iVar4 + 0xc) = unaff_ESI;
        *(int *)(iVar4 + 0x20) = unaff_ESI;
        *(int *)(iVar4 + 0x2c) = unaff_EBX;
        *(int *)(iVar4 + 0x10) = unaff_EBX;
        *(int *)(iVar4 + 0x24) = unaff_EBX;
        FUN_004512d4(unaff_ESI,unaff_EBX);
      }
      piVar1 = (int *)(unaff_EBP + -4);
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        return;
      }
    }
    *(undefined4 *)(unaff_EBP + -8) = 0x24;
    *(undefined4 *)(unaff_EBP + -0xc) = 1;
    if (*(int *)(unaff_EBP + -0xc) < *(int *)(unaff_EBP + -8)) {
      do {
        iVar4 = -1;
        if ((*(byte *)(unaff_EBP + -0xc) & 1) == 0) {
          iVar4 = 1;
        }
        if ((unaff_ESI < 0) || (0x11 < unaff_ESI)) {
          unaff_EBX = unaff_EBX + *(int *)(unaff_EBP + -0xc) * iVar4;
        }
        else {
          *(undefined4 *)(unaff_EBP + -0x10) = *(undefined4 *)(unaff_EBP + -0xc);
          iVar5 = *(int *)(unaff_EBP + -0x10);
          while (0 < iVar5) {
            unaff_EBX = unaff_EBX + iVar4;
            if (((-1 < unaff_EBX) && (unaff_EBX < 0x12)) &&
               (iVar5 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar5 == 0)) {
              iVar5 = FUN_00451b68(unaff_EBP + -0x70);
              if (iVar5 != 0) {
                *(int *)(iVar5 + 0x28) = unaff_ESI;
                *(int *)(iVar5 + 0xc) = unaff_ESI;
                *(int *)(iVar5 + 0x20) = unaff_ESI;
                *(int *)(iVar5 + 0x2c) = unaff_EBX;
                *(int *)(iVar5 + 0x10) = unaff_EBX;
                *(int *)(iVar5 + 0x24) = unaff_EBX;
                FUN_004512d4(unaff_ESI,unaff_EBX);
              }
              piVar1 = (int *)(unaff_EBP + -4);
              *piVar1 = *piVar1 + -1;
              if (*piVar1 == 0) {
                return;
              }
            }
            *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + -1;
            iVar5 = *(int *)(unaff_EBP + -0x10);
          }
        }
        if ((unaff_EBX < 0) || (0x11 < unaff_EBX)) {
          unaff_ESI = unaff_ESI + *(int *)(unaff_EBP + -0xc) * iVar4;
        }
        else {
          *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0xc);
          iVar5 = *(int *)(unaff_EBP + -0x14);
          while (0 < iVar5) {
            unaff_ESI = unaff_ESI + iVar4;
            if (((-1 < unaff_ESI) && (unaff_ESI < 0x12)) &&
               (iVar5 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar5 == 0)) {
              iVar5 = FUN_00451b68(unaff_EBP + -0x70);
              if (iVar5 != 0) {
                *(int *)(iVar5 + 0x28) = unaff_ESI;
                *(int *)(iVar5 + 0xc) = unaff_ESI;
                *(int *)(iVar5 + 0x20) = unaff_ESI;
                *(int *)(iVar5 + 0x2c) = unaff_EBX;
                *(int *)(iVar5 + 0x10) = unaff_EBX;
                *(int *)(iVar5 + 0x24) = unaff_EBX;
                FUN_004512d4(unaff_ESI,unaff_EBX);
              }
              piVar1 = (int *)(unaff_EBP + -4);
              *piVar1 = *piVar1 + -1;
              if (*piVar1 == 0) {
                return;
              }
            }
            *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + -1;
            iVar5 = *(int *)(unaff_EBP + -0x14);
          }
        }
        *(int *)(unaff_EBP + -0xc) = *(int *)(unaff_EBP + -0xc) + 1;
      } while (*(int *)(unaff_EBP + -0xc) < *(int *)(unaff_EBP + -8));
    }
    if (unaff_ESI < 0x12) {
      iVar4 = *(int *)(unaff_EBP + -8);
      while (0 < iVar4) {
        unaff_EBX = unaff_EBX + -1;
        if (((-1 < unaff_EBX) && (unaff_EBX < 0x12)) &&
           (iVar4 = FUN_004511d8(unaff_ESI,unaff_EBX), iVar4 == 0)) {
          iVar4 = FUN_00451b68(unaff_EBP + -0x70);
          if (iVar4 != 0) {
            *(int *)(iVar4 + 0x28) = unaff_ESI;
            *(int *)(iVar4 + 0xc) = unaff_ESI;
            *(int *)(iVar4 + 0x20) = unaff_ESI;
            *(int *)(iVar4 + 0x2c) = unaff_EBX;
            *(int *)(iVar4 + 0x10) = unaff_EBX;
            *(int *)(iVar4 + 0x24) = unaff_EBX;
            FUN_004512d4(unaff_ESI,unaff_EBX);
          }
          piVar1 = (int *)(unaff_EBP + -4);
          *piVar1 = *piVar1 + -1;
          if (*piVar1 == 0) {
            return;
          }
        }
        *(int *)(unaff_EBP + -8) = *(int *)(unaff_EBP + -8) + -1;
        iVar4 = *(int *)(unaff_EBP + -8);
      }
    }
  }
  return;
}

