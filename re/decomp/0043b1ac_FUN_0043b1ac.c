// FUN_0043b1ac @ 0043b1ac size=280 sig=undefined FUN_0043b1ac() cc=unknown
// callers: 
// callees: FUN_0046bdfc,FUN_004a43da

void FUN_0043b1ac(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 8) {
    uVar2 = 0x7d8;
    if (((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] == DAT_0058f1f4) || (DAT_00583c20 != 0)) {
      iVar1 = FUN_0046bdfc(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      iVar1 = iVar1 - DAT_0058f150;
      if (iVar1 < -0x19) {
        uVar2 = 0x7d7;
      }
      else if ((iVar1 < -10) && (-0x1a < iVar1)) {
        uVar2 = 0x7d6;
      }
      else if ((iVar1 < -5) && (-0xb < iVar1)) {
        uVar2 = 0x7d5;
      }
      else if ((iVar1 < 0) && (-6 < iVar1)) {
        uVar2 = 0x7d4;
      }
      else if ((iVar1 < 4) && (0 < iVar1)) {
        uVar2 = 2000;
      }
      else if ((iVar1 < 7) && (3 < iVar1)) {
        uVar2 = 0x7d1;
      }
      else if ((iVar1 < 10) && (6 < iVar1)) {
        uVar2 = 0x7d2;
      }
      else if (9 < iVar1) {
        uVar2 = 0x7d3;
      }
    }
    else {
      uVar2 = 0x7d8;
    }
    FUN_004a43da(param_1,8,param_3,param_4);
    *(undefined4 *)(param_1 + 0x54) = uVar2;
  }
  FUN_004a43da(param_1,param_2,param_3,param_4);
  return;
}

