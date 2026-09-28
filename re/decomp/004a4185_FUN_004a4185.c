// FUN_004a4185 @ 004a4185 size=55 sig=undefined FUN_004a4185() cc=unknown
// callers: FUN_004a421e,FUN_0044b544
// callees: FUN_004a41bc

int FUN_004a4185(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (DAT_0051e384 != 0) {
      param_1 = *(int *)(DAT_0051e384 + 4);
    }
  }
  else {
    while (iVar1 = FUN_004a41bc(param_1), iVar1 != 0) {
      param_1 = FUN_004a41bc(param_1);
    }
  }
  return param_1;
}

