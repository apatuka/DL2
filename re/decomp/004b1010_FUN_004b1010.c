// FUN_004b1010 @ 004b1010 size=134 sig=undefined FUN_004b1010() cc=unknown
// callers: FUN_004b3304,FUN_004b335c,FUN_004b1b38,FUN_004ac718,FUN_00412358,FUN_004b33b0
// callees: FUN_004b0ed4,FUN_004a67ec,FUN_004b0418,FUN_004b0408,FUN_004b0a30,FUN_004b0b44

int FUN_004b1010(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    FUN_004b0a30(param_1);
    param_1 = 0;
  }
  else if (param_1 == 0) {
    param_1 = FUN_004b0b44(param_2);
  }
  else {
    iVar1 = FUN_004b0ed4(param_1,param_2);
    if (iVar1 == 0) {
      FUN_004b0408();
      iVar1 = FUN_004b0b44(param_2);
      if (iVar1 != 0) {
        if ((*(uint *)(param_1 + -4) & 0xfffffffc) <= param_2) {
          param_2 = *(uint *)(param_1 + -4) & 0xfffffffc;
        }
        FUN_004a67ec(iVar1,param_1,param_2);
        FUN_004b0a30(param_1);
      }
      FUN_004b0418();
      param_1 = iVar1;
    }
  }
  return param_1;
}

