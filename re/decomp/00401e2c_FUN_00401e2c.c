// FUN_00401e2c @ 00401e2c size=139 sig=undefined FUN_00401e2c() cc=unknown
// callers: 
// callees: 

void FUN_00401e2c(int param_1,int *param_2)

{
  short *psVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_14;
  int local_10 [3];
  
  piVar2 = &DAT_00522018;
  iVar3 = 0;
  psVar1 = (short *)(param_1 + 0x12);
  do {
    param_2 = param_2 + 1;
    if ((int)*psVar1 < *param_2) {
      local_10[2] = *piVar2 - (*param_2 - (int)*psVar1);
      local_10[1] = 0;
      if (local_10[2] < 0) {
        piVar4 = local_10 + 1;
      }
      else {
        piVar4 = local_10 + 2;
      }
      *piVar2 = *piVar4;
    }
    local_10[0] = (int)*psVar1 - *param_2;
    local_14 = 0;
    if ((int)*psVar1 - *param_2 < 0) {
      piVar4 = &local_14;
    }
    else {
      piVar4 = local_10;
    }
    iVar3 = iVar3 + 1;
    *psVar1 = (short)*piVar4;
    psVar1 = psVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0xb);
  return;
}

