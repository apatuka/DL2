// FUN_0045e0b4 @ 0045e0b4 size=135 sig=undefined FUN_0045e0b4() cc=unknown
// callers: FUN_0045e274,FUN_0044a5e8,FUN_0044a48c,FUN_0045e398,FUN_00449870
// callees: 

void FUN_0045e0b4(int param_1,int param_2)

{
  int *piVar1;
  int local_c [2];
  
  local_c[1] = 0;
  if (param_1 < 1) {
    piVar1 = local_c + 1;
  }
  else {
    piVar1 = &param_1;
  }
  DAT_004c5b54 = *piVar1;
  local_c[0] = 0;
  if (param_2 < 1) {
    piVar1 = local_c;
  }
  else {
    piVar1 = &param_2;
  }
  DAT_004c5b58 = *piVar1;
  if ((int)DAT_004d5b1a < DAT_004c5b54 + DAT_005644c4) {
    DAT_004c5b54 = DAT_004d5b1a - DAT_005644c4;
  }
  if ((int)DAT_004d5b1b < DAT_004c5b58 + DAT_005644c8) {
    DAT_004c5b58 = DAT_004d5b1b - DAT_005644c8;
  }
  return;
}

