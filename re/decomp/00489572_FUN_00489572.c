// FUN_00489572 @ 00489572 size=50 sig=undefined FUN_00489572() cc=unknown
// callers: FUN_00489ae1
// callees: 

undefined4 FUN_00489572(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) || (piVar1 = *(int **)(param_1 + 0x1c), piVar1 == (int *)0x0)) {
    uVar2 = 0;
  }
  else {
    *param_2 = *(undefined4 *)(*piVar1 + 4);
    *param_3 = *(undefined4 *)(*piVar1 + 8);
    uVar2 = 1;
  }
  return uVar2;
}

