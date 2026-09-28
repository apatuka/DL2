// FUN_0046716c @ 0046716c size=106 sig=undefined FUN_0046716c() cc=unknown
// callers: FUN_00468c94
// callees: FUN_00477f9c,FUN_00427e6c,FUN_00427ee8,FUN_00427e80,FUN_00427f04,FUN_00475344
// strings: \"Deadlock 2 is waiting for the master computer to start the game.\"|\"Waiting for Game\"

void FUN_0046716c(void)

{
  int iVar1;
  
  iVar1 = 0;
  FUN_00427e80(1,PTR_s_Waiting_for_Game_00509334,PTR_s_Deadlock_2_is_waiting_for_the_ma_00509338,0,2
              );
  FUN_00427f04();
  while ((((DAT_0058f1fc == 0 && (DAT_0058f1f0 == 0)) && (iVar1 == 0)) && (DAT_004d8264 == 0))) {
    FUN_00477f9c();
    iVar1 = FUN_00427e6c();
  }
  FUN_00427ee8();
  if (iVar1 == 4) {
    FUN_00475344();
    DAT_0058f1f0 = 1;
  }
  return;
}

