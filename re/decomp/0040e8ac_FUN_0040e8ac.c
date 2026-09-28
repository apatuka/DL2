// FUN_0040e8ac @ 0040e8ac size=67 sig=undefined FUN_0040e8ac() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040e868,FUN_0040bbf4,FUN_0040bfb4,FUN_0040beb4

void FUN_0040e8ac(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (((iVar1 != 0) && ((int)*(short *)(param_1 + 10) == (int)*(char *)(iVar1 + 0x20))) &&
     (iVar1 = FUN_0040e868(iVar1), iVar1 != 0)) {
    FUN_0040bfb4(param_1,7);
    FUN_0040bbf4(param_1,0,0);
    return;
  }
  FUN_0040beb4(param_1);
  return;
}

