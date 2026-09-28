// FUN_0040ec04 @ 0040ec04 size=75 sig=undefined FUN_0040ec04() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040eb34,FUN_0040bbf4,FUN_0040c5cc,FUN_0040bfb4,FUN_0040beb4

void FUN_0040ec04(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    uVar1 = FUN_0040eb34(param_1);
    *(undefined4 *)(param_1 + 0x10) = uVar1;
  }
  if (*(int *)(param_1 + 0x10) == 0) {
    FUN_0040beb4(param_1);
  }
  iVar2 = FUN_0040c5cc(param_1);
  if (iVar2 == 0) {
    FUN_0040bbf4(param_1,0,0);
  }
  else {
    FUN_0040bfb4(param_1,0x12);
    FUN_0040beb4(param_1);
  }
  return;
}

