// FUN_0048fb67 @ 0048fb67 size=88 sig=undefined FUN_0048fb67() cc=unknown
// callers: FUN_0048a8c3,FUN_0048a145
// callees: FUN_00488ce9,FUN_0048fa92

int FUN_0048fb67(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  if ((param_1[2] == 1) && (param_1[4] == 0x7fffffff)) {
    iVar1 = FUN_00488ce9(*param_1);
    if (iVar1 == -1) {
      return 0x7fffffff;
    }
    param_1[4] = iVar1;
  }
  else {
    iVar1 = param_1[4];
    if (iVar1 == 0x7fffffff) {
      return 0x7fffffff;
    }
  }
  iVar2 = FUN_0048fa92(param_1);
  return iVar1 - (iVar2 - param_1[5]);
}

