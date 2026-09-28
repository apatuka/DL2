// FUN_00427ee8 @ 00427ee8 size=26 sig=undefined FUN_00427ee8() cc=unknown
// callers: FUN_00479a5c,FUN_0047b4ac,FUN_00429464,FUN_00468898,FUN_00437718,RaceInit,FUN_00479b6c,WinMain,FUN_0045e554,FUN_00479700,FUN_0042836c,RunAITurns,FUN_0046e9d0,FUN_0046716c,FUN_00468a28,FUN_0043793c,SynchronizeGame
// callees: free,FUN_0042824c

void FUN_00427ee8(void)

{
  int iVar1;
  
  iVar1 = DAT_004b7d94;
  if (DAT_004b7d94 != 0) {
    FUN_0042824c(DAT_004b7d94);
    free(iVar1);
  }
  return;
}

