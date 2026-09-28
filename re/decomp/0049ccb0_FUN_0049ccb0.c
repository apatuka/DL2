// FUN_0049ccb0 @ 0049ccb0 size=130 sig=undefined FUN_0049ccb0() cc=unknown
// callers: FUN_0049cd32
// callees: FUN_0049eb44,FUN_0049f09b

int FUN_0049ccb0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 local_18 [4];
  int local_14;
  int local_c;
  int local_8;
  
  iVar1 = FUN_0049eb44(param_1,param_2,2,0x17,0,0);
  FUN_0049eb44(param_1,param_2,2,0x1a,0,0);
  local_8 = FUN_0049eb44(param_1,param_2,2,0x1e,0,0);
  FUN_0049eb44(param_1,param_2,2,0x18,0,0);
  FUN_0049f09b(param_2,local_18);
  iVar2 = (local_c - local_14) / iVar1;
  if ((local_c - local_14) % iVar1 != 0) {
    iVar2 = iVar2 + 1;
  }
  return iVar2 * local_8;
}

