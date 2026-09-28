// FUN_0040e050 @ 0040e050 size=186 sig=undefined FUN_0040e050() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040ab80,FUN_0040c4d4,FUN_0040bbf4,FUN_004412d4,FUN_0040c5cc,FUN_0040bfb4,FUN_0040beb4

void FUN_0040e050(int *param_1)

{
  int iVar1;
  
  iVar1 = param_1[4];
  if (((iVar1 == 0) || (*(short *)(iVar1 + 0x30) != 0)) || (2 < *(short *)(iVar1 + 0xa6c))) {
LAB_0040e0ff:
    FUN_0040beb4(param_1);
  }
  else {
    iVar1 = (int)*(char *)(iVar1 + 0x20);
    if ((iVar1 != -1) && (iVar1 != *(short *)((int)param_1 + 10))) {
      iVar1 = FUN_004412d4((int)*(short *)((int)param_1 + 10),iVar1,2);
      if (iVar1 == 0) goto LAB_0040e0ff;
    }
    if (*param_1 == 2) {
      iVar1 = FUN_0040ab80(param_1,0x19);
    }
    else {
      iVar1 = FUN_0040ab80(param_1,0x1f);
    }
    if (iVar1 != 0) {
      iVar1 = FUN_0040c4d4(param_1[4]);
      param_1[5] = iVar1;
      FUN_0040bbf4(param_1,0,0);
      iVar1 = FUN_0040c5cc(param_1);
      if (iVar1 != 0) {
        if (*param_1 == 2) {
          FUN_0040bfb4(param_1,8);
        }
        else {
          FUN_0040bfb4(param_1,9);
        }
        FUN_0040beb4(param_1);
      }
    }
  }
  return;
}

