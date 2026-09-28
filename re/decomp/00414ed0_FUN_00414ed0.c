// FUN_00414ed0 @ 00414ed0 size=50 sig=undefined FUN_00414ed0() cc=unknown
// callers: 
// callees: FUN_004a60b1,InvalidateRect,FUN_004a5e69

void FUN_00414ed0(int param_1,RECT *param_2)

{
  if (*(int *)(param_1 + 0x24) != 0) {
    InvalidateRect(*(HWND *)(param_1 + 0x24),param_2,1);
  }
  FUN_004a5e69(0,0);
  FUN_004a60b1(param_2,0);
  return;
}

