// FUN_00481c80 @ 00481c80 size=288 sig=undefined FUN_00481c80() cc=unknown
// callers: FUN_0048180c,FUN_00481540
// callees: 

void FUN_00481c80(int param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6,
                 int param_7,int param_8)

{
  int iVar1;
  
  *param_6 = param_7;
  *param_5 = param_7;
  if (param_8 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (param_7 + 1) * param_8;
  }
  if (param_1 < param_8) {
    if (DAT_004d59b4 == 0x4a) {
      *param_3 = (param_7 + 1) * param_1 + DAT_004b7d4c;
    }
    else {
      *param_3 = (param_7 + 1) * param_1 + DAT_004c5478;
    }
    *param_5 = *param_5 + 1;
  }
  else if (DAT_004d59b4 == 0x4a) {
    *param_3 = (param_1 - param_8) * param_7 + iVar1 + DAT_004b7d4c;
  }
  else {
    *param_3 = (param_1 - param_8) * param_7 + iVar1 + DAT_004c5478;
  }
  if (param_2 < param_8) {
    if (DAT_004d59b4 == 0x4a) {
      *param_4 = (param_7 + 1) * param_2 + DAT_004b7d48;
    }
    else {
      *param_4 = (param_7 + 1) * param_2 + DAT_004c547c;
    }
    *param_6 = *param_6 + 1;
  }
  else if (DAT_004d59b4 == 0x4a) {
    *param_4 = (param_2 - param_8) * param_7 + iVar1 + DAT_004b7d48;
  }
  else {
    *param_4 = (param_2 - param_8) * param_7 + iVar1 + DAT_004c547c;
  }
  return;
}

