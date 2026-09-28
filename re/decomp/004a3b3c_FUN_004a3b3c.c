// FUN_004a3b3c @ 004a3b3c size=148 sig=undefined FUN_004a3b3c() cc=unknown
// callers: FUN_004a3d26
// callees: FUN_00498ba9,FUN_00495454,FUN_0048f774,FUN_004989cf,FUN_004955b2

int FUN_004a3b3c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00498ba9(0x130);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    FUN_0048f774(iVar1,0x130,0);
    iVar2 = 0;
    do {
      *(undefined4 *)(iVar1 + 0x120 + iVar2 * 4) = 0xffffffff;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 3);
    *(undefined4 *)(iVar1 + 0x54) = param_7;
    *(undefined4 *)(iVar1 + 8) = param_1;
    *(undefined4 *)(iVar1 + 0xc) = param_2;
    *(undefined4 *)(iVar1 + 0x10) = param_3;
    *(undefined4 *)(iVar1 + 0x14) = param_4;
    *(undefined4 *)(iVar1 + 0x20) = param_5;
    *(undefined4 *)(iVar1 + 0x1c) = param_6;
    iVar2 = FUN_004955b2(0,0);
    *(int *)(iVar1 + 300) = iVar2;
    if (iVar2 == 0) {
      FUN_004989cf(iVar1);
      iVar1 = 0;
    }
    else {
      FUN_00495454(DAT_0051e384,iVar1,0);
    }
  }
  return iVar1;
}

