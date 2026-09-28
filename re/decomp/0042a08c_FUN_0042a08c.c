// FUN_0042a08c @ 0042a08c size=462 sig=undefined FUN_0042a08c() cc=unknown
// callers: FUN_0042a2c4
// callees: FUN_0049fd2e,FUN_004a10d0

void FUN_0042a08c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  
  iVar2 = FUN_004a10d0(DAT_004b9bf0,0x4d);
  if (iVar2 != 0) {
    iVar3 = FUN_004a10d0(DAT_004b9bf0,0x4e);
    if (iVar3 != 0) {
      iVar4 = FUN_004a10d0(DAT_004b9bf0,0x4f);
      if (iVar4 != 0) {
        iVar5 = FUN_004a10d0(DAT_004b9bf0,0x50);
        if (iVar5 != 0) {
          iVar6 = FUN_004a10d0(DAT_004b9bf0,0x51);
          if (iVar6 != 0) {
            piVar8 = &DAT_00557bb4;
            for (iVar7 = 0; iVar7 < DAT_004d5aec + -1; iVar7 = iVar7 + 1) {
              if ('\x02' < (char)(&DAT_0059f161)[*piVar8 * 0x2d8]) {
                iVar1 = *(int *)(&DAT_005220a4 + DAT_0058f1f4 * 4 + *piVar8 * 0x1c);
                if ((iVar1 < -0x32) || (-0x14 < iVar1)) {
                  if ((iVar1 < -0x13) || (-10 < iVar1)) {
                    if ((iVar1 < -9) || (9 < iVar1)) {
                      if ((iVar1 < 10) || (0x13 < iVar1)) {
                        if ((0x13 < iVar1) && (iVar1 < 0x33)) {
                          FUN_0049fd2e(iVar2,&DAT_004b9e3c + iVar7 * 0x10,0,0,0,
                                       *(undefined4 *)(iVar2 + 0x54),0);
                        }
                      }
                      else {
                        FUN_0049fd2e(iVar3,&DAT_004b9e3c + iVar7 * 0x10,0,0,0,
                                     *(undefined4 *)(iVar3 + 0x54),0);
                      }
                    }
                    else {
                      FUN_0049fd2e(iVar4,&DAT_004b9e3c + iVar7 * 0x10,0,0,0,
                                   *(undefined4 *)(iVar4 + 0x54),0);
                    }
                  }
                  else {
                    FUN_0049fd2e(iVar5,&DAT_004b9e3c + iVar7 * 0x10,0,0,0,
                                 *(undefined4 *)(iVar5 + 0x54),0);
                  }
                }
                else {
                  FUN_0049fd2e(iVar6,&DAT_004b9e3c + iVar7 * 0x10,0,0,0,
                               *(undefined4 *)(iVar6 + 0x54),0);
                }
              }
              piVar8 = piVar8 + 1;
            }
          }
        }
      }
    }
  }
  return;
}

