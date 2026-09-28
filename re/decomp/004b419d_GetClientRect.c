// GetClientRect @ 004b419d size=6 sig=BOOL GetClientRect(HWND hWnd, LPRECT lpRect) cc=__stdcall
// callers: FUN_00465070,FUN_00465540,FUN_004655b0,FUN_00457bec
// callees: 

BOOL GetClientRect(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b419d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetClientRect(hWnd,lpRect);
  return BVar1;
}

