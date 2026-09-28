// FUN_00444948 @ 00444948 size=35 sig=undefined FUN_00444948() cc=unknown
// callers: @WinGWndProc$qqspvuiuil
// callees: GetParent,PostMessageA

void FUN_00444948(HWND param_1,WPARAM param_2,LPARAM param_3)

{
  HWND hWnd;
  
  hWnd = GetParent(param_1);
  PostMessageA(hWnd,0x1a0a,param_2,param_3);
  return;
}

