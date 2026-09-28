// FUN_0042ebb8 @ 0042ebb8 size=183 sig=undefined FUN_0042ebb8() cc=unknown
// callers: FUN_0042ec70
// callees: FUN_00436070,FUN_0042836c,FUN_0042ea98,FUN_0042e8c0,FUN_0048db5d,FUN_004a2cb5,FUN_0042ea8c,FUN_00436064,FUN_0046578c,UpdateWindow
// strings: \"Are you sure you want to clear the high score list?\"|\"Clear High Scores\"

longlong FUN_0042ebb8(void)

{
  int iVar1;
  uint local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042ea8c();
  iVar1 = FUN_004a2cb5(DAT_004c3744,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004c3744 + 100) == 0)) {
    if (local_8 == 0x39) {
      DAT_004d59a4 = 0;
      return 0x3900000039;
    }
    if (local_8 == 0x3a) {
      iVar1 = FUN_0042836c(PTR_s_Clear_High_Scores_00509908,
                           PTR_s_Are_you_sure_you_want_to_clear_t_0050990c,0x28a1,0,1);
      FUN_00436070();
      FUN_00436064();
      FUN_0042ea98();
      if (iVar1 == 1) {
        FUN_0046578c();
        FUN_0042e8c0();
      }
      FUN_0042ea8c();
      UpdateWindow(DAT_004d5978);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_8 << 0x20;
}

