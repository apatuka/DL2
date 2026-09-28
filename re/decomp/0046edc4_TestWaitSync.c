// TestWaitSync @ 0046edc4 size=73 sig=undefined TestWaitSync() cc=unknown
// callers: 
// callees: FUN_0046c9cc,sprintf,DebugMessage,FUN_004ae5d8
// strings: \"TestWaitSync\"|\"Random Number sync at %d = %ld %d\"

/* auto-named from string evidence: TestWaitSync */

void TestWaitSync(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_84 [128];
  
  uVar1 = FUN_0046c9cc(s_TestWaitSync_004d5cc4);
  iVar2 = FUN_004ae5d8();
  sprintf(local_84,s_Random_Number_sync_at__d____ld___004d5cd1,param_1,uVar1,iVar2 % 0xffff);
  DebugMessage(local_84);
  return;
}

