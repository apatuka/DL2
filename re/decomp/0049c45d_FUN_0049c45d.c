// FUN_0049c45d @ 0049c45d size=237 sig=undefined FUN_0049c45d() cc=unknown
// callers: FUN_0049f267
// callees: FUN_00495d89,FUN_0049bb73

undefined4 FUN_0049c45d(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 local_14 [16];
  
  iVar1 = FUN_0049bb73(param_1,param_2,1,local_14);
  if ((iVar1 != 0) && (iVar1 = FUN_00495d89(local_14,param_3,param_4), iVar1 != 0)) {
    return 1;
  }
  iVar1 = FUN_0049bb73(param_1,param_2,2,local_14);
  if ((iVar1 != 0) && (iVar1 = FUN_00495d89(local_14,param_3,param_4), iVar1 != 0)) {
    return 2;
  }
  iVar1 = FUN_0049bb73(param_1,param_2,3,local_14);
  if ((iVar1 != 0) && (iVar1 = FUN_00495d89(local_14,param_3,param_4), iVar1 != 0)) {
    return 3;
  }
  iVar1 = FUN_0049bb73(param_1,param_2,5,local_14);
  if ((iVar1 != 0) && (iVar1 = FUN_00495d89(local_14,param_3,param_4), iVar1 != 0)) {
    return 5;
  }
  iVar1 = FUN_0049bb73(param_1,param_2,6,local_14);
  if ((iVar1 != 0) && (iVar1 = FUN_00495d89(local_14,param_3,param_4), iVar1 != 0)) {
    return 6;
  }
  return 0;
}

