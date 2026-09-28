// FUN_00481a5c @ 00481a5c size=292 sig=undefined FUN_00481a5c() cc=unknown
// callers: FUN_0045d6a4,FUN_0045d630,FUN_00413428,FUN_0045c27c,FUN_0045d3a4,FUN_0045c704,FUN_0042f224,FUN_00427440,FUN_00421fc4,FUN_0045ca3c,FUN_00427ab0,FUN_00432824,FUN_0045b448,FUN_0044a0e0,FUN_0045d478
// callees: 

void FUN_00481a5c(int param_1,int param_2,int *param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_004d59b4 == 0x4a) {
    local_8 = (DAT_004b7d50 - DAT_004b7d48) / (int)DAT_004d5b1b;
    local_c = (DAT_004b7d54 - DAT_004b7d4c) / (int)DAT_004d5b1a;
    if (local_c < local_8) {
      piVar1 = &local_c;
    }
    else {
      piVar1 = &local_8;
    }
    iVar2 = *piVar1;
    iVar3 = (DAT_004b7d54 - DAT_004b7d4c) - DAT_004d5b1a * iVar2;
  }
  else {
    local_10 = DAT_004c5484 / (int)DAT_004d5b1b;
    local_14 = DAT_004c5480 / (int)DAT_004d5b1a;
    if (DAT_004c5480 / (int)DAT_004d5b1a < DAT_004c5484 / (int)DAT_004d5b1b) {
      piVar1 = &local_14;
    }
    else {
      piVar1 = &local_10;
    }
    iVar2 = *piVar1;
    iVar3 = DAT_004c5480 - DAT_004d5b1a * iVar2;
  }
  if (iVar3 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = (iVar2 + 1) * iVar3;
  }
  if (iVar4 < param_1) {
    *param_3 = (param_1 - iVar4) / iVar2 + iVar3;
  }
  else {
    *param_3 = param_1 / (iVar2 + 1);
  }
  if (iVar4 < param_2) {
    *param_4 = iVar3 + (param_2 - iVar4) / iVar2;
  }
  else {
    *param_4 = param_2 / (iVar2 + 1);
  }
  return;
}

