// KillTimer @ 004b413d size=6 sig=BOOL KillTimer(HWND hWnd, UINT_PTR uIDEvent) cc=__stdcall
// callers: FUN_0044a2e0,FUN_00472d74,FUN_00469234
// callees: 

BOOL KillTimer(HWND hWnd,UINT_PTR uIDEvent)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b413d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = KillTimer(hWnd,uIDEvent);
  return BVar1;
}

