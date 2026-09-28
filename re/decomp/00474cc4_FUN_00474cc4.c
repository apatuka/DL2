// FUN_00474cc4 @ 00474cc4 size=54 sig=undefined FUN_00474cc4() cc=unknown
// callers: BroadcastText,BroadcastBlock,MasterDispatchNetMessage,FUN_00475344,BroadcastDirect,FUN_00475f80,FUN_004779c0,SynchronizeGame,SendSlaveInfo,BroadcastBlockDirect,SpecialBroadcast
// callees: FUN_004152e0,FUN_00458550,FUN_004585cc

void FUN_00474cc4(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00458550(param_2,param_3,0);
  if (iVar1 != -1) {
    if (iVar1 == 0) {
      FUN_004585cc();
    }
    else if (iVar1 == 1) {
      FUN_004152e0();
      DAT_004d59a4 = DAT_004d59a4 | 4;
    }
  }
  return;
}

