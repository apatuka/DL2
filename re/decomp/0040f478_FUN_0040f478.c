// FUN_0040f478 @ 0040f478 size=130 sig=undefined FUN_0040f478() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040f3d8,FUN_0040c510,FUN_0040c3b8,FUN_0040bbf4,FUN_0040f060,FUN_0040bfb4,FUN_0040c5cc,FUN_0040beb4

void FUN_0040f478(int param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_0040bfb4(param_1,1);
  FUN_0040bfb4(param_1,0xf);
  iVar1 = FUN_0040f3d8(param_1);
  *(int *)(param_1 + 0x10) = iVar1;
  if ((iVar1 == 0) || ((int)*(short *)(param_1 + 8) != (int)*(char *)(iVar1 + 0x20))) {
    FUN_0040beb4(param_1);
  }
  else {
    FUN_0040bbf4(param_1,0,0);
    iVar2 = FUN_0040c510(iVar1);
    *(int *)(param_1 + 0x14) = iVar2 * 2;
    iVar2 = FUN_0040c3b8(param_1);
    iVar1 = FUN_0040c510(iVar1);
    if (iVar1 <= iVar2) {
      iVar1 = FUN_0040c5cc(param_1);
      if (iVar1 != 0) {
        FUN_0040bfb4(param_1,0);
        FUN_0040f060(param_1);
      }
    }
  }
  return;
}

