// FUN_00453210 @ 00453210 size=121 sig=undefined FUN_00453210() cc=unknown
// callers: FUN_00453a38,FUN_00455c88,FUN_00453ec8,FUN_00453c30,FUN_00454690,FUN_00455468,FUN_00454160,FUN_004543f8
// callees: 

void FUN_00453210(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  
  iVar1 = (char)(&DAT_004f9dc5)[*(short *)(param_1 + 4) * 0x32] * 3 + -2;
  if (*(int *)(param_1 + 6) < param_2) {
    if (*(int *)(param_1 + 6) + iVar1 < param_2) {
      *param_4 = *(int *)(param_1 + 6) + iVar1;
    }
    else {
      *param_4 = param_2;
    }
  }
  else {
    *param_4 = *(int *)(param_1 + 6);
  }
  if (*(int *)(param_1 + 10) < param_3) {
    iVar1 = *(int *)(param_1 + 10) + iVar1;
    if (iVar1 < param_3) {
      *param_5 = iVar1;
    }
    else {
      *param_5 = param_3;
    }
  }
  else {
    *param_5 = *(int *)(param_1 + 10);
  }
  return;
}

