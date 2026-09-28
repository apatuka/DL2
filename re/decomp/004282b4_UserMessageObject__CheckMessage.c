// UserMessageObject__CheckMessage @ 004282b4 size=184 sig=undefined UserMessageObject__CheckMessage() cc=unknown
// callers: FUN_00427e6c
// callees: FUN_0048db5d,DebugMessage,FUN_004a2cb5,FUN_00414f38,FUN_00426594
// strings: \"gpMessage NULL in UserMessageObject::CheckMessage()\"

/* auto-named from string evidence: UserMessageObject::CheckMessage */

undefined4 UserMessageObject__CheckMessage(int *param_1)

{
  int iVar1;
  int local_8;
  
  if (param_1[1] == 0) {
    DebugMessage(s_gpMessage_NULL_in_UserMessageObj_004b7d98);
    return 0;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00414f38(param_1[1]);
  iVar1 = FUN_004a2cb5(param_1[1],&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(param_1[1] + 100) == 0)) {
    if (local_8 == 3) {
      DAT_004d59a4 = 0;
      return 3;
    }
    if (local_8 == 4) {
      DAT_004d59a4 = 0;
      return 4;
    }
    if (local_8 == 5) {
      if (*param_1 == 0) {
        FUN_00426594(&DAT_004d4d64);
      }
      else {
        FUN_00426594(*param_1);
      }
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

