// FUN_0049b416 @ 0049b416 size=38 sig=undefined FUN_0049b416() cc=unknown
// callers: FUN_004369dc,FUN_00415624
// callees: FUN_00498ba9

int * FUN_0049b416(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00498ba9(param_1 * 4 + 4);
  if (piVar1 != (int *)0x0) {
    *piVar1 = param_1;
  }
  return piVar1;
}

