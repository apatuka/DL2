// FUN_00494e62 @ 00494e62 size=85 sig=undefined FUN_00494e62() cc=unknown
// callers: 
// callees: FUN_00494c15,Sleep,PeekMessageA,ExitThread

void FUN_00494e62(void)

{
  BOOL BVar1;
  tagMSG local_20;
  
  while (DAT_0051dc84 == 0) {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x200,0x200,1);
    if (BVar1 == 0) {
      FUN_00494c15();
    }
    else if (local_20.message == 0x200) {
      FUN_00494c15();
    }
    Sleep(DAT_0051dca0);
  }
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}

