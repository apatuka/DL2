// FUN_00495a4a @ 00495a4a size=45 sig=undefined FUN_00495a4a() cc=unknown
// callers: FUN_00489ae1
// callees: FUN_00495811,FUN_00491159,FUN_0049585a

void FUN_00495a4a(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    FUN_00495811(param_1);
    iVar1 = FUN_00491159(0,param_2);
    *(int *)(param_1 + 0x3c) = iVar1;
    if (iVar1 != 0) {
      FUN_0049585a(param_1);
    }
  }
  return;
}

