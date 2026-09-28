// FUN_00415180 @ 00415180 size=135 sig=undefined FUN_00415180() cc=unknown
// callers: FUN_0042662c
// callees: FUN_0048d2e7,FUN_00414e5c,FUN_0049a9e7,FUN_0049a8ed,InvalidateRect,FUN_0048d32c,FUN_00493784,UpdateWindow,FUN_0049a93f

void FUN_00415180(undefined4 param_1,int param_2)

{
  HWND pHVar1;
  RECT *lpRect;
  BOOL bErase;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_004d5c28 != 0) {
    FUN_0048d2e7(DAT_004d5c28);
    FUN_0049a8ed();
    local_14 = 0;
    local_10 = 0;
    local_8 = 0x1e0;
    local_c = 0x280;
    FUN_0049a9e7(&local_14);
    FUN_00493784(local_14,local_10,local_c,local_8,param_1,0,1);
    FUN_0049a93f();
    FUN_0048d32c();
    bErase = 0;
    lpRect = (RECT *)0x0;
    pHVar1 = (HWND)FUN_00414e5c();
    InvalidateRect(pHVar1,lpRect,bErase);
    if (param_2 != 0) {
      pHVar1 = (HWND)FUN_00414e5c();
      UpdateWindow(pHVar1);
    }
  }
  return;
}

