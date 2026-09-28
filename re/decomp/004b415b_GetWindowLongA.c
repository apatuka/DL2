// GetWindowLongA @ 004b415b size=6 sig=LONG GetWindowLongA(HWND hWnd, int nIndex) cc=__stdcall
// callers: CreateWinGWindow,FUN_004442dc,StillPic,FUN_00444398,FUN_00465584,FUN_00444370,FUN_00457bec,FUN_0043e22c
// callees: 

LONG GetWindowLongA(HWND hWnd,int nIndex)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b415b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = GetWindowLongA(hWnd,nIndex);
  return LVar1;
}

