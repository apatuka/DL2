// SetWindowLongA @ 004b4149 size=6 sig=LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong) cc=__stdcall
// callers: FUN_004442dc,FUN_00444370
// callees: 

LONG SetWindowLongA(HWND hWnd,int nIndex,LONG dwNewLong)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4149. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SetWindowLongA(hWnd,nIndex,dwNewLong);
  return LVar1;
}

