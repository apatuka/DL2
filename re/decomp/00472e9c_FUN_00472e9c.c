// FUN_00472e9c @ 00472e9c size=51 sig=undefined FUN_00472e9c() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: GetActiveWindow,FUN_00472e4c,InvalidateRect,FUN_00472e84

void FUN_00472e9c(int param_1)

{
  HWND hWnd;
  
  if (param_1 == 0) {
    FUN_00472e84(1);
  }
  else {
    hWnd = GetActiveWindow();
    if (hWnd != (HWND)0x0) {
      InvalidateRect(hWnd,(RECT *)0x0,0);
    }
    FUN_00472e4c();
  }
  return;
}

