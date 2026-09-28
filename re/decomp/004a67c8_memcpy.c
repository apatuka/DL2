// memcpy @ 004a67c8 size=36 sig=undefined memcpy() cc=unknown
// callers: FUN_00474ea8,FUN_00411b54,StillPic,FUN_004b343c,FUN_00479324,FUN_0047bfdc,FUN_00479164,FUN_00465070,SynchronizeGame,CreateWinGWindow,FUN_004b3208,FUN_00465640,CreateMainWindow,FUN_00460870,FUN_00479eb0,SendTerritoryData,FUN_0047c4c0,FUN_0047bf20,FUN_004770fc,FUN_004ac260,FUN_0046338c,FUN_0045fae4,FUN_004acaf4,FUN_004aa0dc,FUN_004a7df4,FUN_004aa718,FUN_0047b98c,FUN_004605e0,FUN_004a6b48,FUN_0047c03c,FUN_004618e8,FUN_0047c128,NetReceiveCapsule,FUN_00467c8c,FUN_004b2380,FUN_004a723b,FUN_004a78a4,FUN_0045f664,MasterDispatchNetMessage,FUN_004ac414,FUN_0047c430,FUN_004a9d10,FUN_004782ec,FUN_004aa20c,BroadcastBlock,FUN_0047b8b4,TestMemory,FUN_0047b4ac,FUN_004684d0,FUN_004323d0,SendSlaveInfo,FUN_0047b660,BroadcastBlockDirect,FUN_00479a2c,FUN_004657e0,FUN_004314d8,FUN_00474e84,FUN_00460258,CalculateGameCRC,FUN_0047bebc,FUN_0046a700
// callees: 

/* RTL */

undefined4 * memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  return param_1;
}

