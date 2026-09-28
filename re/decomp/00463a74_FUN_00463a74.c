// FUN_00463a74 @ 00463a74 size=38 sig=undefined FUN_00463a74() cc=unknown
// callers: CreateMainWindow,FUN_00467c8c,StillPic,FUN_0046338c,TestMemory,FUN_004684d0,CreateWinGWindow
// callees: InvalidateRect,FUN_004639dc,FUN_004639f4

undefined4 FUN_00463a74(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004639dc(DAT_004d597c);
  InvalidateRect(DAT_0058f1a4,(RECT *)0x0,0);
  FUN_004639f4();
  return uVar1;
}

