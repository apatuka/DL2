// FUN_0044de9c @ 0044de9c size=145 sig=undefined FUN_0044de9c() cc=unknown
// callers: FUN_00485668,_DemolishBuilding,FUN_0044db50,CheckBuildingList,FUN_0047d068,FUN_00402df4,FUN_00471f5c,FUN_00407e78,DoRiot,FUN_0047f440,FUN_00408310,FUN_004526b0,FUN_00451de4,SetItemStats,FUN_00401f44,FUN_0046aa10,FUN_0044f110
// callees: FUN_0044de48

void FUN_0044de9c(char *param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  *param_4 = (int)*(short *)(&DAT_004f9dc6 + param_2 * 0x32);
  iVar1 = 0;
  piVar4 = (int *)(&DAT_004fa71c + param_2 * 0x2c);
  piVar3 = param_4;
  do {
    piVar3 = piVar3 + 1;
    *piVar3 = *piVar4;
    iVar1 = iVar1 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar1 < 0xb);
  if (param_2 == 0x25) {
    iVar1 = FUN_0044de48((int)*param_1);
    if (iVar1 == 0) {
      param_4[1] = param_4[1] >> 2;
    }
    else {
      iVar2 = 0;
      piVar4 = param_4;
      do {
        piVar4 = piVar4 + 1;
        iVar2 = iVar2 + 1;
        *piVar4 = iVar1 * *piVar4;
      } while (iVar2 < 0xb);
    }
  }
  param_4[0xc] = (int)(char)(&DAT_004f9de3)[param_2 * 0x32];
  return;
}

