// FUN_0040b968 @ 0040b968 size=41 sig=undefined FUN_0040b968() cc=unknown
// callers: FUN_0040b994
// callees: RemoveArmyFromTaskForce,FUN_0040c3b8,FUN_0040b0c0

void FUN_0040b968(int param_1,undefined4 param_2)

{
  int iVar1;
  
  RemoveArmyFromTaskForce(param_2);
  iVar1 = FUN_0040c3b8(param_1);
  if (iVar1 < *(int *)(param_1 + 0x14)) {
    FUN_0040b0c0(param_1,param_2);
  }
  return;
}

