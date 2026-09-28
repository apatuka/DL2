// FUN_00412358 @ 00412358 size=241 sig=undefined FUN_00412358() cc=unknown
// callers: 
// callees: FUN_004b0b44,FUN_004b1010,FUN_004aa48c,FUN_004a6b48,FUN_004aa518

undefined4 FUN_00412358(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[3] == 1) {
    uVar1 = 0;
  }
  else {
    if (*param_1 == 0) {
      param_1[2] = 1;
      iVar2 = FUN_004b0b44(0xe);
      *param_1 = iVar2;
      if (iVar2 == 0) {
        return 0;
      }
    }
    else {
      param_1[2] = param_1[2] + 1;
      iVar2 = FUN_004b1010(*param_1,param_1[2] * 0xe);
      *param_1 = iVar2;
      if (iVar2 == 0) {
        param_1[2] = param_1[2] + -1;
        return 0;
      }
    }
    iVar2 = FUN_004aa48c(param_1[4]);
    if (iVar2 < 0) {
      uVar1 = 0;
    }
    else {
      iVar3 = FUN_004aa518(&param_4,4,1,param_1[4]);
      if (iVar3 == 1) {
        iVar3 = FUN_004aa518(param_3,1,param_4,param_1[4]);
        if (iVar3 == param_4) {
          FUN_004a6b48(param_1[1] * 0xe + *param_1,param_2,8);
          uVar1 = 1;
          *(int *)(*param_1 + 10 + param_1[1] * 0xe) = iVar2;
          param_1[1] = param_1[1] + 1;
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

