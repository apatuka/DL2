// FUN_00472ed0 @ 00472ed0 size=72 sig=undefined FUN_00472ed0() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: FUN_00415274,FUN_004152c0,FUN_00472e4c,FUN_00494def,FUN_0048e0f7,FUN_00472e68,FUN_00414e5c

void FUN_00472ed0(short param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    FUN_00472e68();
    if (DAT_0051daf8 != 0) {
      FUN_004152c0();
      FUN_0048e0f7();
    }
  }
  else {
    FUN_00472e4c();
    if (DAT_0051daf8 != 0) {
      uVar1 = FUN_00414e5c();
      FUN_00415274(uVar1);
      FUN_00494def(1);
    }
  }
  return;
}

