// FUN_0048394c @ 0048394c size=87 sig=undefined FUN_0048394c() cc=unknown
// callers: FUN_00483bd4,FUN_00483b84,FUN_0043cc5c
// callees: FUN_004b0a30

undefined4 FUN_0048394c(int *param_1,undefined2 *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)0x0;
  piVar2 = (int *)*param_1;
  while( true ) {
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    if (param_2 == &DAT_004fbbac + *piVar2 * 0x19) break;
    piVar1 = piVar2;
    piVar2 = (int *)piVar2[1];
  }
  if (piVar1 == (int *)0x0) {
    *param_1 = piVar2[1];
  }
  else {
    piVar1[1] = piVar2[1];
  }
  FUN_004b0a30(piVar2);
  return 1;
}

