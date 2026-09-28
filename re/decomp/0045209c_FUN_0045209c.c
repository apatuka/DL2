// FUN_0045209c @ 0045209c size=436 sig=undefined FUN_0045209c() cc=unknown
// callers: FUN_00456150,FUN_00456e44
// callees: FUN_004512a8,FUN_0045130c,FUN_00451340

void FUN_0045209c(int param_1)

{
  ushort uVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  ushort *local_c;
  int local_8;
  
  FUN_004512a8();
  iVar4 = 0;
  pbVar5 = &DAT_0057ce00;
  do {
    iVar2 = 0;
    pbVar3 = pbVar5;
    do {
      if ((((iVar4 < 9) || (iVar2 < 9)) || (0x1a < iVar4)) || (0x1a < iVar2)) {
        *pbVar3 = *pbVar3 | 0x70;
      }
      iVar2 = iVar2 + 1;
      pbVar3 = pbVar3 + 0x24;
    } while (iVar2 < 0x24);
    iVar4 = iVar4 + 1;
    pbVar5 = pbVar5 + 1;
  } while (iVar4 < 0x24);
  local_8 = 0;
  local_c = (ushort *)(param_1 + 2);
  do {
    iVar4 = (local_8 % 6) * 3;
    iVar2 = (local_8 / 6) * 3;
    if (*local_c == 0xff) {
      uVar1 = 6;
    }
    else {
      uVar1 = *local_c & 0xf;
    }
    FUN_00451340(iVar4,iVar2,uVar1);
    FUN_00451340(iVar4 + 1,iVar2,uVar1);
    FUN_00451340(iVar4 + 2,iVar2,uVar1);
    FUN_00451340(iVar4,iVar2 + 1,uVar1);
    FUN_00451340(iVar4 + 1,iVar2 + 1,uVar1);
    FUN_00451340(iVar4 + 2,iVar2 + 1,uVar1);
    FUN_00451340(iVar4,iVar2 + 2,uVar1);
    FUN_00451340(iVar4 + 1,iVar2 + 2,uVar1);
    FUN_00451340(iVar4 + 2,iVar2 + 2,uVar1);
    if (DAT_004cf850 == 0) {
      *(short *)(DAT_0057cdf8 + 0x2c + local_8 * 2) = (short)(char)local_c[7];
    }
    uVar1 = *(ushort *)(DAT_0057cdf8 + 0x2c + local_8 * 2);
    if (((uVar1 != 0) && (uVar1 != 2)) && (uVar1 != 4)) {
      FUN_0045130c(iVar4,iVar2,1);
    }
    if ((uVar1 & 4) != 0) {
      FUN_0045130c(iVar4,iVar2 + 1,1);
      FUN_0045130c(iVar4,iVar2 + 2,1);
    }
    if (uVar1 == 1) {
      FUN_0045130c(iVar4,iVar2 + 1,1);
    }
    if ((uVar1 & 2) != 0) {
      FUN_0045130c(iVar4 + 1,iVar2,1);
      FUN_0045130c(iVar4 + 2,iVar2,1);
    }
    if (uVar1 == 8) {
      FUN_0045130c(iVar4 + 1,iVar2,1);
    }
    local_8 = local_8 + 1;
    local_c = local_c + 0x1a;
  } while (local_8 < 0x24);
  return;
}

