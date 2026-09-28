// InvalidateRect @ 004b414f size=6 sig=BOOL InvalidateRect(HWND hWnd, RECT * lpRect, BOOL bErase) cc=__stdcall
// callers: CreateWinGWindow,FUN_00458c6c,FUN_0043e0dc,FUN_0044a000,FUN_00422344,FUN_00414f38,FUN_00443830,FUN_00458d80,FUN_00472e9c,FUN_00463a74,FUN_004691f8,FUN_004655b0,FUN_00414ea4,FUN_00415208,FUN_0043e22c,FUN_00468a28,FUN_00449dec,FUN_0043e058,FUN_00415180,FUN_00480b80,FUN_00482320,FUN_0045deb0,FUN_00472e4c,FUN_00414ed0,StillPic,FUN_00487df4
// callees: 

BOOL InvalidateRect(HWND hWnd,RECT *lpRect,BOOL bErase)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b414f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = InvalidateRect(hWnd,lpRect,bErase);
  return BVar1;
}

