// DefWindowProcA @ 004b41df size=6 sig=LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) cc=__stdcall
// callers: @MainWndProc$qqspvuiuil,@IntroWndProc$qqspvuiuil,@WinGWndProc$qqspvuiuil,FUN_0048b1c0,@CustomWnd$qqspvuiuil,@BackWndProc$qqspvuiuil
// callees: 

LRESULT DefWindowProcA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b41df. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = DefWindowProcA(hWnd,Msg,wParam,lParam);
  return LVar1;
}

