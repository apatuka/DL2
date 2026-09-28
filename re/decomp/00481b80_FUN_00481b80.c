// FUN_00481b80 @ 00481b80 size=256 sig=undefined FUN_00481b80() cc=unknown
// callers: FUN_00481da0,FUN_0048192c
// callees: 

void FUN_00481b80(int param_1,int param_2,int *param_3,int *param_4,int param_5,int param_6)

{
  int iVar1;
  
  if (param_6 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (param_5 + 1) * param_6;
  }
  if (param_1 < param_6) {
    if (DAT_004d59b4 == 0x4a) {
      *param_3 = (param_5 + 1) * param_1 + DAT_004b7d4c;
    }
    else {
      *param_3 = (param_5 + 1) * param_1 + DAT_004c5478;
    }
  }
  else if (DAT_004d59b4 == 0x4a) {
    *param_3 = (param_1 - param_6) * param_5 + iVar1 + DAT_004b7d4c;
  }
  else {
    *param_3 = (param_1 - param_6) * param_5 + iVar1 + DAT_004c5478;
  }
  if (param_2 < param_6) {
    if (DAT_004d59b4 == 0x4a) {
      *param_4 = (param_5 + 1) * param_2 + DAT_004b7d48;
    }
    else {
      *param_4 = (param_5 + 1) * param_2 + DAT_004c547c;
    }
  }
  else if (DAT_004d59b4 == 0x4a) {
    *param_4 = iVar1 + (param_2 - param_6) * param_5 + DAT_004b7d48;
  }
  else {
    *param_4 = iVar1 + (param_2 - param_6) * param_5 + DAT_004c547c;
  }
  return;
}

