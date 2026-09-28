// FUN_0041800c @ 0041800c size=75 sig=undefined FUN_0041800c() cc=unknown
// callers: FUN_004180b0
// callees: FUN_00417f0c

void FUN_0041800c(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x48);
  iVar2 = *param_3;
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x3c) == *(int *)(param_1 + 0x3c))) {
    FUN_00417f0c(iVar1,param_2,param_3);
  }
  if (iVar2 == 1) {
    *param_3 = 3;
  }
  else if (iVar2 == 4) {
    *param_3 = 6;
  }
  else {
    *param_2 = *param_2 + 1;
  }
  return;
}

