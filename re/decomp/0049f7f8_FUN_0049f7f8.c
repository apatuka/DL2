// FUN_0049f7f8 @ 0049f7f8 size=70 sig=undefined FUN_0049f7f8() cc=unknown
// callers: FUN_0049d5e9
// callees: FUN_0049ea99,FUN_0049eb44,FUN_0049eb20,FUN_00495c51

void FUN_0049f7f8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_14 [16];
  
  iVar1 = FUN_0049ea99(param_1);
  FUN_0049eb44(iVar1,param_1,2,0x1d,param_2,local_14);
  FUN_00495c51(local_14,*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0xc));
  FUN_0049eb20(iVar1,local_14);
  return;
}

