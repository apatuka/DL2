// GetWindowRect @ 004b4155 size=6 sig=BOOL GetWindowRect(HWND hWnd, LPRECT lpRect) cc=__stdcall
// callers: FUN_0046d1dc,CYGame_InitDirectDraw,FUN_00472f64,FUN_0046d180,FUN_00444398
// callees: 

BOOL GetWindowRect(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4155. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetWindowRect(hWnd,lpRect);
  return BVar1;
}

