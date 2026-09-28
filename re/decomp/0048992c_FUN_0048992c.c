// FUN_0048992c @ 0048992c size=80 sig=undefined FUN_0048992c() cc=unknown
// callers: FUN_0048997c
// callees: FUN_00489524,_SmackNextFrame@4

undefined4 FUN_0048992c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x1c) == 0)) {
    uVar2 = 0;
  }
  else {
    iVar1 = **(int **)(param_1 + 0x1c);
    if (((*(byte *)(param_1 + 0x14) & 4) == 0) &&
       (*(int *)(iVar1 + 0xc) + -1 == *(int *)(iVar1 + 0x374))) {
      FUN_00489524(param_1,1);
      uVar2 = 0;
    }
    else {
      _SmackNextFrame_4(iVar1);
      FUN_00489524(param_1,3);
      uVar2 = 1;
    }
  }
  return uVar2;
}

