// FUN_0040beb4 @ 0040beb4 size=253 sig=undefined FUN_0040beb4() cc=unknown
// callers: FUN_0040dbc4,FUN_0040eadc,FUN_0040ec04,FUN_0040f540,FUN_0040e8ac,FUN_0040f4fc,FUN_0040e050,FUN_0040e384,FUN_0040ad88,FUN_00403350,FUN_0040e6e4,FUN_0040f2e0,FUN_00407594,FUN_0040e994,FUN_0040dd68,FUN_0040f478
// callees: RemoveArmyFromTaskForce,FUN_0040b000,memset,FUN_0040afa4,FUN_0040b0c0

void FUN_0040beb4(int param_1)

{
  int *piVar1;
  int iVar2;
  int local_c;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  if (*(int *)(param_1 + 0x84) != 0) {
    local_8 = &DAT_005224c0 + *(short *)(param_1 + 10) * 0x2648 + *(int *)(param_1 + 0x84) * 0xc4;
  }
  piVar1 = (int *)(param_1 + 0x44);
  local_c = 0;
  do {
    iVar2 = *piVar1;
    if (iVar2 != 0) {
      if ((local_8 == (undefined *)0x0) || ((&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24] != '\x01'))
      {
        *(undefined2 *)(iVar2 + 0x36) = 0;
      }
      else {
        RemoveArmyFromTaskForce(iVar2);
        FUN_0040b0c0(local_8,iVar2);
      }
    }
    local_c = local_c + 1;
    piVar1 = piVar1 + 1;
  } while (local_c < 0x10);
  iVar2 = 1;
  piVar1 = (int *)(param_1 + 0x88);
  do {
    if (*piVar1 != 0) {
      FUN_0040b000(&DAT_00522584 + *(short *)(param_1 + 10) * 0x2648,
                   &DAT_005224c0 + *(short *)(param_1 + 10) * 0x2648 + *piVar1 * 0xc4);
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  if (local_8 != (undefined *)0x0) {
    FUN_0040afa4(local_8,param_1);
  }
  memset(param_1,0,0xc4);
  return;
}

