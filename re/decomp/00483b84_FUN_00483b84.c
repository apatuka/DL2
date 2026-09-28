// FUN_00483b84 @ 00483b84 size=78 sig=undefined FUN_00483b84() cc=unknown
// callers: FUN_00483bd4,FUN_0043cc5c
// callees: FUN_00483a30,FUN_0048394c

void FUN_00483b84(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)*param_2;
  while (piVar2 != (int *)0x0) {
    iVar3 = FUN_00483a30(param_1,*param_2,*piVar2);
    if (iVar3 == 0) {
      piVar1 = (int *)piVar2[1];
      FUN_0048394c(param_2,&DAT_004fbbac + *piVar2 * 0x19);
      piVar2 = piVar1;
    }
    else {
      piVar2 = (int *)piVar2[1];
    }
  }
  return;
}

