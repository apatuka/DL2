// FUN_00427e80 @ 00427e80 size=49 sig=undefined FUN_00427e80() cc=unknown
// callers: FUN_00429464,FUN_00468898,FUN_00437718,FUN_0047997c,FUN_00479b6c,FUN_0045e554,FUN_00479de4,FUN_00479700,FUN_0042836c,FUN_0043793c,FUN_0046716c,FUN_00468a28
// callees: FUN_00427fe0,FUN_004b02a8

undefined4
FUN_00427e80(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_004b02a8(0x10);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00427fe0(iVar1,param_1,param_2,param_3,param_4,param_5);
  }
  return uVar2;
}

