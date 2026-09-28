// FUN_00427eb4 @ 00427eb4 size=49 sig=undefined FUN_00427eb4() cc=unknown
// callers: FUN_0047b4ac,RaceInit,WinMain,RunAITurns,FUN_0046e980,SynchronizeGame
// callees: FUN_004281f4,FUN_004b02a8

undefined4
FUN_00427eb4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004b02a8(0x10);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_004281f4(iVar1,param_1,param_2,param_3,param_4,param_5);
  }
  return uVar2;
}

