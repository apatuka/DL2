// FUN_00487df4 @ 00487df4 size=62 sig=undefined FUN_00487df4() cc=unknown
// callers: FUN_00487e34
// callees: UpdateWindow,InvalidateRect

void FUN_00487df4(int param_1)

{
  HWND hWnd;
  
  hWnd = DAT_004d5974;
  if ((DAT_004d5974 == (HWND)0x0) && (hWnd = (HWND)0x0, DAT_004d5978 != (HWND)0x0)) {
    hWnd = DAT_004d5978;
  }
  if ((hWnd != (HWND)0x0) && (InvalidateRect(hWnd,(RECT *)0x0,0), param_1 != 0)) {
    UpdateWindow(hWnd);
  }
  return;
}

