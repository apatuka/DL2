// FUN_004b002c @ 004b002c size=150 sig=undefined FUN_004b002c() cc=unknown
// callers: FUN_004b1fb4
// callees: 

undefined4 FUN_004b002c(byte *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  
  while( true ) {
    bVar1 = *param_1;
    uVar2 = (uint)bVar1;
    pbVar3 = param_1 + 1;
    if (((&DAT_0069f56d)[bVar1] & 4) == 0) {
      if (((&DAT_005209ce)[uVar2 * 2] & 2) != 0) {
        uVar2 = uVar2 - 0x20;
      }
    }
    else if (*pbVar3 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (uint)CONCAT11(bVar1,*pbVar3);
      pbVar3 = param_1 + 2;
    }
    bVar1 = *param_2;
    uVar4 = (uint)bVar1;
    pbVar5 = param_2 + 1;
    if (((&DAT_0069f56d)[bVar1] & 4) == 0) {
      if (((&DAT_005209ce)[uVar4 * 2] & 2) != 0) {
        uVar4 = uVar4 - 0x20;
      }
    }
    else if (*pbVar5 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = (uint)CONCAT11(bVar1,*pbVar5);
      pbVar5 = param_2 + 2;
    }
    if (uVar4 != uVar2) break;
    param_1 = pbVar3;
    param_2 = pbVar5;
    if (uVar2 == 0) {
      return 0;
    }
  }
  if (uVar2 < uVar4) {
    return 0xffffffff;
  }
  return 1;
}

