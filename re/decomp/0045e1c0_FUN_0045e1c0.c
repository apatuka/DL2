// FUN_0045e1c0 @ 0045e1c0 size=179 sig=undefined FUN_0045e1c0() cc=unknown
// callers: FUN_0044a5e8,FUN_0044a48c
// callees: 

void FUN_0045e1c0(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int local_14;
  int local_10 [3];
  
  local_10[2] = 0;
  if (param_1 < 1) {
    piVar1 = local_10 + 2;
  }
  else {
    piVar1 = &param_1;
  }
  local_10[1] = 0;
  if (param_2 < 1) {
    piVar2 = local_10 + 1;
  }
  else {
    piVar2 = &param_2;
  }
  local_10[0] = DAT_00657dd8 - (DAT_004c5460 - DAT_004c5b60);
  if (*piVar1 < local_10[0]) {
    piVar1 = &param_1;
  }
  else {
    piVar1 = local_10;
  }
  local_14 = DAT_00657ddc - (DAT_004c5464 - DAT_004c5b64);
  if (*piVar2 < local_14) {
    piVar2 = &param_2;
  }
  else {
    piVar2 = &local_14;
  }
  DAT_004dcc24 = *piVar1;
  DAT_004dcc28 = *piVar2;
  return;
}

