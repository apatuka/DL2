// GetUpdateRect @ 004b4209 size=6 sig=BOOL GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase) cc=__stdcall
// callers: FUN_004655b0
// callees: 

BOOL GetUpdateRect(HWND hWnd,LPRECT lpRect,BOOL bErase)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4209. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetUpdateRect(hWnd,lpRect,bErase);
  return BVar1;
}

