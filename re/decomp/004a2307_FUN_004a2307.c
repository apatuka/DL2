// FUN_004a2307 @ 004a2307 size=111 sig=undefined FUN_004a2307() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049eaae

void FUN_004a2307(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_2 != 0) &&
     (((param_3 != 0 && ((*(byte *)(param_2 + 0x28) & 4) == 0)) ||
      ((param_3 == 0 && ((*(byte *)(param_2 + 0x28) & 4) != 0)))))) {
    FUN_0049eb44(param_1,param_2,2,8,0,0);
    uVar1 = 2;
    if (param_3 == 0) {
      uVar1 = 0;
    }
    FUN_0049eaae(param_2,uVar1);
    FUN_0049eb44(param_1,param_2,2,8,0,0);
    FUN_0049eb44(param_1,param_2,2,0x32,0,0);
  }
  return;
}

