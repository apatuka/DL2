// FUN_00414e74 @ 00414e74 size=12 sig=undefined FUN_00414e74() cc=unknown
// callers: FUN_0046e9d0,WinMain
// callees: FUN_00414e5c,UpdateWindow

void FUN_00414e74(void)

{
  HWND hWnd;
  
  hWnd = (HWND)FUN_00414e5c();
  UpdateWindow(hWnd);
  return;
}

