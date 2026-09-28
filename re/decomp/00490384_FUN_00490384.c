// FUN_00490384 @ 00490384 size=46 sig=undefined FUN_00490384() cc=unknown
// callers: FUN_004905e5,FUN_004903d6
// callees: 

int FUN_00490384(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xc);
  piVar1 = (int *)(param_1 + 0x14);
  while( true ) {
    if (iVar2 < 1) {
      return 0;
    }
    if (param_2 == *piVar1) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + -1;
  }
  return param_1 + piVar1[1];
}

