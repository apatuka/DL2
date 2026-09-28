// FUN_0040c510 @ 0040c510 size=40 sig=undefined FUN_0040c510() cc=unknown
// callers: FUN_0040f2e0,FUN_0040f478
// callees: 

int FUN_0040c510(int param_1)

{
  int *piVar1;
  int local_8;
  
  piVar1 = (int *)(param_1 + 0xa58);
  local_8 = 0;
  if (*piVar1 < 0) {
    piVar1 = &local_8;
  }
  return *piVar1;
}

