// FUN_004a33f3 @ 004a33f3 size=32 sig=undefined FUN_004a33f3() cc=unknown
// callers: FUN_004a3533,FUN_004a3413,FUN_004a39f7
// callees: FUN_004a335b

void FUN_004a33f3(int param_1)

{
  int *piVar1;
  
  for (piVar1 = (int *)(param_1 + 4); *piVar1 != -1; piVar1 = (int *)FUN_004a335b(piVar1)) {
  }
  FUN_004a335b(piVar1);
  return;
}

