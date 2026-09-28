// FUN_0045539c @ 0045539c size=201 sig=undefined FUN_0045539c() cc=unknown
// callers: FUN_004556b0,FUN_00457048
// callees: FUN_00450de0,FUN_00446084,FUN_00444fd4,FUN_0045328c,FUN_004512f0,FUN_0043da44,FUN_004482cc

void FUN_0045539c(int *param_1)

{
  int iVar1;
  
  *(undefined1 *)((int)param_1 + 0x1d) = 0;
  param_1[8] = 0x7f;
  param_1[9] = 0x7f;
  iVar1 = FUN_00450de0(param_1);
  if (iVar1 == 0) {
    DAT_005649e4 = DAT_005649e4 + -1;
  }
  else {
    DAT_005649e0 = DAT_005649e0 + -1;
  }
  FUN_0045328c(param_1);
  FUN_004512f0(param_1[10],param_1[0xb]);
  if ((&DAT_004faf8d)[param_1[1] * 0x24] == '\x02') {
    FUN_004512f0(param_1[8],param_1[9]);
  }
  if (DAT_004cf850 == 0) {
    if ((*(short *)((int)param_1 + 0x1a) != -1) && (*param_1 != 0)) {
      iVar1 = *param_1;
      *(undefined1 *)(iVar1 + 10) = 0x7f;
      *(undefined4 *)(iVar1 + 0x44) = 0;
      iVar1 = FUN_00446084(iVar1,&DAT_005a43d0 + *(short *)((int)param_1 + 0x1a) * 0xadc,0);
      if (iVar1 == 0) {
        param_1[8] = 0x7e;
      }
    }
  }
  else {
    FUN_00444fd4(param_1[0xe]);
    iVar1 = FUN_004482cc(param_1);
    if (iVar1 != 0) {
      FUN_0043da44(param_1);
    }
  }
  return;
}

