// SendMessageA @ 004b40d7 size=6 sig=LRESULT SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) cc=__stdcall
// callers: FUN_0040c8c8,@MainWndProc$qqspvuiuil,FUN_00405d54,FUN_0046d124,FUN_00457b3c,@CheatTechDialog$qqspvuiuil
// callees: 

LRESULT SendMessageA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40d7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SendMessageA(hWnd,Msg,wParam,lParam);
  return LVar1;
}

