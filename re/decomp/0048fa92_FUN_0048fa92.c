// FUN_0048fa92 @ 0048fa92 size=76 sig=undefined FUN_0048fa92() cc=unknown
// callers: FUN_0048a4d2,FUN_0048fade,FUN_004a65e0,FUN_00497d40,FUN_00491200,FUN_004917e6,FUN_0048fb67
// callees: FUN_00488c95

int FUN_0048fa92(undefined4 *param_1)

{
  int iVar1;
  
  if ((param_1[2] == 1) || (param_1[2] == 2)) {
    if (param_1[6] == 0) {
      iVar1 = FUN_00488c95(*param_1,0,1);
    }
    else {
      iVar1 = FUN_00488c95(*param_1,0,1);
      if (0 < iVar1) {
        iVar1 = iVar1 - param_1[3];
      }
    }
  }
  else {
    iVar1 = param_1[3];
  }
  return iVar1;
}

