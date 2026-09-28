// FUN_0046c3fc @ 0046c3fc size=160 sig=undefined FUN_0046c3fc() cc=unknown
// callers: FUN_0044bea8,FUN_0044980c,FUN_0046c49c,FUN_0043b2c4,FUN_00442978,FUN_0044bacc,FUN_00480d78,FUN_00402548,FUN_0043b50c,FUN_0044339c,FUN_0046e730
// callees: 

void FUN_0046c3fc(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_10;
  int local_c [2];
  
  iVar2 = (*(char *)(param_1 + 0x27) + 9) / 10;
  iVar1 = iVar2 * -10;
  iVar4 = iVar1 + 100;
  if (iVar4 < 0) {
    iVar4 = iVar1 + 0x67;
  }
  *param_2 = ((int)*(short *)(param_1 + 0x30) * ((iVar4 >> 2) + iVar2 * 10)) / 10000;
  if (*(short *)(param_1 + 0x30) != 0) {
    local_c[1] = 1;
    piVar3 = param_2;
    if (*param_2 < 1) {
      piVar3 = local_c + 1;
    }
    *param_2 = *piVar3;
  }
  local_c[0] = (int)*(short *)(param_1 + 0x30) / 100 - *param_2;
  local_10 = 0;
  if (local_c[0] < 0) {
    piVar3 = &local_10;
  }
  else {
    piVar3 = local_c;
  }
  *param_3 = *piVar3;
  return;
}

