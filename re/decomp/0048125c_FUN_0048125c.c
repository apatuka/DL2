// FUN_0048125c @ 0048125c size=152 sig=undefined FUN_0048125c() cc=unknown
// callers: FUN_004812f4,FUN_0048149c
// callees: 

void FUN_0048125c(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  
  if (param_3 < DAT_00657de4) {
    piVar2 = &param_3;
  }
  else {
    piVar2 = &DAT_00657de4;
  }
  DAT_00657dd8 = *piVar2;
  if (param_4 < DAT_00657de8) {
    piVar2 = &param_4;
  }
  else {
    piVar2 = &DAT_00657de8;
  }
  DAT_00657ddc = *piVar2;
  piVar2 = &DAT_006566cc;
  for (iVar1 = 0; iVar1 < DAT_00657ddc; iVar1 = iVar1 + 1) {
    *piVar2 = *(int *)(DAT_004dcc1c + 0x10) * iVar1;
    piVar2 = piVar2 + 1;
  }
  DAT_00657dd0 = DAT_00657dd8 >> 1;
  DAT_00657dd4 = (DAT_00657ddc >> 1) + -0x96;
  DAT_004dcc14 = param_1;
  DAT_004dcc18 = param_2;
  return;
}

