// FUN_004a3413 @ 004a3413 size=38 sig=undefined FUN_004a3413() cc=unknown
// callers: FUN_004a3533
// callees: FUN_004a33f3

int FUN_004a3413(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; *param_1 != -1; param_1 = (int *)FUN_004a33f3(param_1)) {
    if (*param_1 != 1000) {
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}

