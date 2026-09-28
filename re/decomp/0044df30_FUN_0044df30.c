// FUN_0044df30 @ 0044df30 size=97 sig=undefined FUN_0044df30() cc=unknown
// callers: _DemolishBuilding,FUN_0046aa10,FUN_0044f110
// callees: 

void FUN_0044df30(int param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  *param_2 = (int)DAT_004fa500;
  iVar2 = 0;
  piVar4 = &DAT_004fad78;
  piVar3 = param_2;
  do {
    piVar3 = piVar3 + 1;
    *piVar3 = *piVar4;
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar2 < 0xb);
  param_2[0xc] = (int)DAT_004fa51d;
  sVar1 = *(short *)(param_1 + 0xc);
  if (sVar1 < 1) {
    param_2[1] = param_2[1] >> 2;
  }
  else {
    iVar2 = 0;
    do {
      param_2 = param_2 + 1;
      iVar2 = iVar2 + 1;
      *param_2 = (int)sVar1 * *param_2;
    } while (iVar2 < 0xb);
  }
  return;
}

