// FUN_00472334 @ 00472334 size=101 sig=undefined FUN_00472334() cc=unknown
// callers: FUN_00472448,FUN_004723cc
// callees: 

undefined4 FUN_00472334(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = 1;
  piVar2 = (int *)(param_1 + 0x3e);
  piVar3 = param_3;
  do {
    piVar3 = piVar3 + 1;
    if (*piVar2 < *piVar3) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0xb);
  iVar1 = 1;
  piVar2 = (int *)(param_2 + 0x3e);
  piVar3 = (int *)(param_1 + 0x3e);
  do {
    param_3 = param_3 + 1;
    iVar1 = iVar1 + 1;
    *piVar3 = *piVar3 - *param_3;
    piVar3 = piVar3 + 1;
    *piVar2 = *piVar2 + *param_3;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0xb);
  return 1;
}

