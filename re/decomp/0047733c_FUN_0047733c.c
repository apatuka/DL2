// FUN_0047733c @ 0047733c size=88 sig=undefined FUN_0047733c() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_004ae594,sprintf,DebugMessage,FUN_0046ca60
// strings: \"Reseeded with seed %lX\"

void FUN_0047733c(int param_1)

{
  undefined4 uVar1;
  undefined1 local_104 [256];
  
  uVar1 = *(undefined4 *)(param_1 + 0x1a);
  FUN_004ae594(uVar1);
  FUN_0046ca60(uVar1);
  sprintf(local_104,s_Reseeded_with_seed__lX_004dc1c7,uVar1);
  DebugMessage(local_104);
  return;
}

