// FUN_004867d8 @ 004867d8 size=136 sig=undefined FUN_004867d8() cc=unknown
// callers: FUN_004865e8
// callees: FUN_00486564,FUN_004864c4,FUN_00445040

void FUN_004867d8(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  iVar2 = FUN_00486564(param_3);
  if (iVar2 == -1) {
    iVar2 = 0;
    param_4 = 0;
  }
  *(short *)(param_5 + 0x30) = (short)iVar2;
  FUN_004864c4(param_5,param_1,param_2);
  if (param_4 == 0) {
    *(undefined2 *)(param_5 + 0x22) = 0;
    *(undefined2 *)(param_5 + 0x24) = 0;
  }
  else {
    iVar1 = (&DAT_00512688)[iVar2];
    param_4 = param_4 * DAT_005124e4;
    *(short *)(param_5 + 0x22) = (short)((int)(&DAT_00512668)[iVar2] / param_4);
    *(short *)(param_5 + 0x24) = (short)(iVar1 / param_4);
  }
  FUN_00445040(param_5,iVar2,1);
  return;
}

