// FUN_0040f2e0 @ 0040f2e0 size=246 sig=undefined FUN_0040f2e0() cc=unknown
// callers: FUN_0040f540,FUN_0040e6e4
// callees: FUN_0040be04,FUN_0040c510,FUN_0040ace4,FUN_0040c3b8,FUN_0040ef18,FUN_0040f060,FUN_0040bbf4,FUN_0040beb4,FUN_0040c68c,FUN_0040effc,FUN_0040bfb4,FUN_0040f2a4,FUN_0040f248

void FUN_0040f2e0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = (int)*(short *)(param_1 + 10);
  iVar1 = (int)*(short *)(param_1 + 8);
  iVar3 = *(int *)(param_1 + 0x10);
  FUN_0040bfb4(param_1,1);
  FUN_0040bfb4(param_1,0xf);
  FUN_0040effc(param_1);
  if ((iVar3 == 0) || (*(char *)(iVar3 + 0x20) != iVar1)) {
    FUN_0040beb4(param_1);
  }
  else {
    if (*(char *)(iVar3 + 0x21) == '\0') {
      iVar2 = FUN_0040c68c(iVar4,0xe,iVar3);
      if (iVar2 == 0) {
        FUN_0040be04(iVar4,0xffffffff,iVar1,iVar3,0xe,(int)*(short *)(param_1 + 0xe));
      }
    }
    else {
      iVar2 = FUN_0040c68c(iVar4,6,iVar3);
      if (iVar2 == 0) {
        FUN_0040be04(iVar4,0xffffffff,iVar1,iVar3,6,(int)*(short *)(param_1 + 0xe));
      }
    }
    iVar1 = FUN_0040c510(iVar3);
    *(int *)(param_1 + 0x14) = iVar1 * 2;
    FUN_0040f248(param_1);
    iVar1 = FUN_0040c3b8(param_1);
    iVar3 = FUN_0040c510(iVar3);
    if ((iVar1 < iVar3) && (iVar3 = FUN_0040ace4(param_1), iVar3 < 0x10)) {
      FUN_0040ef18(param_1);
      return;
    }
    iVar3 = FUN_0040f2a4(param_1);
    if (iVar3 != 0) {
      FUN_0040bfb4(param_1,0);
      FUN_0040f060(param_1);
      FUN_0040bbf4(param_1,0,3);
    }
  }
  return;
}

