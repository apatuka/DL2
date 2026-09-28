// FUN_0040eadc @ 0040eadc size=88 sig=undefined FUN_0040eadc() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040c4d4,FUN_0040bbf4,FUN_0040e9f4,FUN_0040beb4

void FUN_0040eadc(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if ((iVar1 == 0) || ((int)*(short *)(param_1 + 8) != (int)*(char *)(iVar1 + 0x20))) {
    FUN_0040beb4(param_1);
  }
  else {
    iVar2 = FUN_0040e9f4(param_1);
    *(int *)(param_1 + 0x10) = iVar2;
    if (iVar2 == 0) {
      FUN_0040beb4(param_1);
    }
    else {
      uVar3 = FUN_0040c4d4(iVar2);
      *(undefined4 *)(param_1 + 0x14) = uVar3;
      FUN_0040bbf4(param_1,0,0);
    }
    *(int *)(param_1 + 0x10) = iVar1;
  }
  return;
}

