// FUN_00427e6c @ 00427e6c size=19 sig=undefined FUN_00427e6c() cc=unknown
// callers: FUN_0044930c,FUN_00429464,FUN_00468898,FUN_00437718,FUN_0045e554,WaitSync,FUN_0042836c,FUN_0043793c,FUN_0046716c
// callees: UserMessageObject__CheckMessage

undefined4 FUN_00427e6c(void)

{
  undefined4 uVar1;
  
  if (DAT_004b7d94 == 0) {
    return 0;
  }
  uVar1 = UserMessageObject__CheckMessage(DAT_004b7d94);
  return uVar1;
}

