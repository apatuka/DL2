// FUN_004a3f2e @ 004a3f2e size=120 sig=undefined FUN_004a3f2e() cc=unknown
// callers: FUN_004a4025
// callees: FUN_004a1150,FUN_004954a9,FUN_004989cf,FUN_004a3ea0

undefined4 FUN_004a3f2e(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    iVar2 = FUN_004a1150(param_1,param_2,param_3);
    if (iVar2 == 0) {
      return local_8;
    }
    if (*(int *)(iVar2 + 0x40) == 0) {
      FUN_004a3ea0(param_1,iVar2);
    }
    else {
      iVar1 = (**(code **)(iVar2 + 0x40))(iVar2,2,0,0);
      if (iVar1 == 0) {
        FUN_004a3ea0(param_1,iVar2);
      }
    }
    FUN_004954a9(*(undefined4 *)(param_1 + 300),iVar2);
    FUN_004989cf(iVar2);
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
    local_8 = 1;
    if (param_3 == 0) break;
    if (param_3 == 2) {
      return 1;
    }
  }
  return 1;
}

