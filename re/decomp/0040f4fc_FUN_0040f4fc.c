// FUN_0040f4fc @ 0040f4fc size=67 sig=undefined FUN_0040f4fc() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040ace4,FUN_0040bbf4,FUN_0040beb4

void FUN_0040f4fc(int param_1)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 0x10) == 0) ||
     ((int)*(short *)(param_1 + 8) != (int)*(char *)(*(int *)(param_1 + 0x10) + 0x20))) {
    FUN_0040beb4(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x14) = 1000000;
    iVar1 = FUN_0040ace4(param_1);
    if (3 < iVar1) {
      FUN_0040bbf4(param_1,0,3);
    }
  }
  return;
}

