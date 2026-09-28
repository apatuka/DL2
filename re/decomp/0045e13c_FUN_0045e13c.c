// FUN_0045e13c @ 0045e13c size=131 sig=undefined FUN_0045e13c() cc=unknown
// callers: FUN_0045e274,FUN_0044a5e8,FUN_0044a48c,FUN_0045e398
// callees: 

void FUN_0045e13c(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  if (DAT_00559dd8 < param_1) {
    piVar1 = &param_1;
  }
  else {
    piVar1 = &DAT_00559dd8;
  }
  param_1 = *piVar1;
  if (*piVar1 < DAT_00559ddc) {
    piVar1 = &param_1;
  }
  else {
    piVar1 = &DAT_00559ddc;
  }
  param_1 = *piVar1;
  if (DAT_00559de0 < param_2) {
    piVar2 = &param_2;
  }
  else {
    piVar2 = &DAT_00559de0;
  }
  param_2 = *piVar2;
  if (*piVar2 < DAT_00559de4) {
    puVar3 = &param_2;
  }
  else {
    puVar3 = &DAT_00559de4;
  }
  DAT_004c4a58 = *piVar1;
  DAT_004c4a5c = *puVar3;
  return;
}

