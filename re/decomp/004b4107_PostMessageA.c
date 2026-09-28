// PostMessageA @ 004b4107 size=6 sig=BOOL PostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) cc=__stdcall
// callers: GetNetGameOptions,FUN_00444948,FUN_0048ba34,FUN_00457b3c,FUN_00413250
// callees: 

BOOL PostMessageA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4107. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PostMessageA(hWnd,Msg,wParam,lParam);
  return BVar1;
}

