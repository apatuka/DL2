// FUN_00417fb4 @ 00417fb4 size=87 sig=undefined FUN_00417fb4() cc=unknown
// callers: FUN_004180b0
// callees: FUN_00417f0c

void FUN_00417fb4(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *param_3;
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x48);
  do {
    if (*piVar2 != 0) {
      FUN_00417f0c(*piVar2,param_2,param_3);
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 3);
  if (iVar1 == 1) {
    *param_3 = 6;
  }
  else {
    *param_2 = *param_2 + 1;
  }
  return;
}

