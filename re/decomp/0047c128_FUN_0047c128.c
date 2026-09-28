// FUN_0047c128 @ 0047c128 size=776 sig=undefined FUN_0047c128() cc=unknown
// callers: FUN_0047c53c
// callees: FUN_00484da8,FUN_00484c40,FUN_0047510c,FUN_00484c2c,FUN_004b02a8,memcpy,FUN_004750c4

void FUN_0047c128(int param_1)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *local_24;
  undefined4 *local_20;
  int local_10;
  
  iVar1 = param_1 + 0x4c900;
  piVar5 = &DAT_005a5846;
  for (local_10 = 1; local_10 <= DAT_004d5b18; local_10 = local_10 + 1) {
    if (*piVar5 != 0) {
      FUN_00484c40(*piVar5,3);
    }
    if (piVar5[1] != 0) {
      FUN_00484c40(piVar5[1],3);
    }
    if (piVar5[2] != 0) {
      FUN_00484c40(piVar5[2],3);
    }
    if (piVar5[3] != 0) {
      FUN_00484c40(piVar5[3],3);
    }
    if (piVar5[4] != 0) {
      FUN_00484c40(piVar5[4],3);
    }
    memcpy(&DAT_005a43d0 + local_10 * 0xadc,local_10 * 0xaf0 + param_1,0xadc);
    if (piVar5[-0x249] != 0) {
      iVar4 = FUN_0047510c(piVar5[-0x249]);
      piVar5[-0x249] = iVar4;
    }
    if (piVar5[-0x248] != 0) {
      iVar4 = FUN_0047510c(piVar5[-0x248]);
      piVar5[-0x248] = iVar4;
    }
    puVar2 = (uint *)((int)piVar5 + -0x91a);
    for (iVar4 = 0; iVar4 < (char)piVar5[-0x247]; iVar4 = iVar4 + 1) {
      *puVar2 = (uint)(&DAT_005a0550 + (*puVar2 >> 0x10) * 400 + (uint)(ushort)*puVar2 * 10);
      puVar2 = puVar2 + 1;
    }
    iVar4 = 0;
    piVar6 = (int *)((int)piVar5 + -0x846);
    do {
      if (*piVar6 != 0) {
        iVar3 = FUN_004750c4(*piVar6);
        *piVar6 = iVar3;
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 0xd;
    } while (iVar4 < 0x24);
    iVar4 = FUN_004b02a8(8);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00484c2c(iVar4);
    }
    *piVar5 = iVar4;
    iVar4 = FUN_004b02a8(8);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00484c2c(iVar4);
    }
    piVar5[1] = iVar4;
    iVar4 = FUN_004b02a8(8);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00484c2c(iVar4);
    }
    piVar5[2] = iVar4;
    iVar4 = FUN_004b02a8(8);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00484c2c(iVar4);
    }
    piVar5[3] = iVar4;
    iVar4 = FUN_004b02a8(8);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = FUN_00484c2c(iVar4);
    }
    piVar5[4] = iVar4;
    piVar5 = piVar5 + 0x2b7;
  }
  local_24 = (int *)(param_1 + 0x15cc);
  local_20 = &DAT_005a5846;
  for (local_10 = 1; local_10 < DAT_004d5b18; local_10 = local_10 + 1) {
    for (iVar4 = 0; iVar4 < *local_24; iVar4 = iVar4 + 1) {
      FUN_00484da8(*local_20,iVar1);
      iVar1 = iVar1 + 0x30;
    }
    for (iVar4 = 0; iVar4 < local_24[1]; iVar4 = iVar4 + 1) {
      FUN_00484da8(local_20[1],iVar1);
      iVar1 = iVar1 + 0x30;
    }
    for (iVar4 = 0; iVar4 < local_24[2]; iVar4 = iVar4 + 1) {
      FUN_00484da8(local_20[2],iVar1);
      iVar1 = iVar1 + 0x30;
    }
    for (iVar4 = 0; iVar4 < local_24[3]; iVar4 = iVar4 + 1) {
      FUN_00484da8(local_20[3],iVar1);
      iVar1 = iVar1 + 0x30;
    }
    for (iVar4 = 0; iVar4 < local_24[4]; iVar4 = iVar4 + 1) {
      FUN_00484da8(local_20[4],iVar1);
      iVar1 = iVar1 + 0x30;
    }
    local_24 = local_24 + 700;
    local_20 = local_20 + 0x2b7;
  }
  return;
}

