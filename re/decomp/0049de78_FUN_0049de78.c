// FUN_0049de78 @ 0049de78 size=52 sig=undefined FUN_0049de78() cc=unknown
// callers: FUN_0049e47a
// callees: strlen

void FUN_0049de78(int *param_1)

{
  int iVar1;
  
  if (*param_1 == 0) {
    param_1[7] = 0;
    param_1[6] = 0;
  }
  else {
    iVar1 = strlen(*param_1);
    if ((param_1[7] < 0) || (iVar1 < param_1[7])) {
      param_1[7] = iVar1;
      param_1[6] = iVar1;
    }
  }
  return;
}

