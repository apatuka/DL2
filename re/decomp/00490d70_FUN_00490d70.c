// FUN_00490d70 @ 00490d70 size=40 sig=undefined FUN_00490d70() cc=unknown
// callers: FUN_0049117e
// callees: FUN_00490603

undefined4 FUN_00490d70(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 == 0) {
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_00490603(param_1);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

