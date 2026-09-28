// FUN_00445aac @ 00445aac size=54 sig=undefined FUN_00445aac() cc=unknown
// callers: FUN_00446084
// callees: ReLinkArmy

void FUN_00445aac(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x48);
  do {
    if (*piVar1 != 0) {
      ReLinkArmy(*piVar1,param_2,param_3,param_4);
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 3);
  return;
}

