// ShowWindow @ 004b41a3 size=6 sig=BOOL ShowWindow(HWND hWnd, int nCmdShow) cc=__stdcall
// callers: CYGame_CreateWindow,CreateMainWindow
// callees: 

BOOL ShowWindow(HWND hWnd,int nCmdShow)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b41a3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ShowWindow(hWnd,nCmdShow);
  return BVar1;
}

