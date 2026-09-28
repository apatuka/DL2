// FUN_004b0118 @ 004b0118 size=187 sig=undefined FUN_004b0118() cc=unknown
// callers: FUN_004b18ac
// callees: 

undefined4 FUN_004b0118(byte *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = param_2;
  while( true ) {
    if (param_3 == 0) {
      return 0;
    }
    bVar1 = *param_1;
    uVar3 = (uint)bVar1;
    pbVar6 = param_1 + 1;
    iVar4 = param_3 + -1;
    if (((&DAT_0069f56d)[bVar1] & 4) == 0) {
      if (((&DAT_005209ce)[uVar3 * 2] & 2) != 0) {
        uVar3 = uVar3 - 0x20;
      }
    }
    else {
      if (iVar4 == 0) {
        return 0;
      }
      if (*pbVar6 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = (uint)CONCAT11(bVar1,*pbVar6);
        pbVar6 = param_1 + 2;
      }
    }
    bVar1 = *pbVar2;
    uVar5 = (uint)bVar1;
    param_2 = pbVar2 + 1;
    if (((&DAT_0069f56d)[bVar1] & 4) == 0) {
      if (((&DAT_005209ce)[uVar5 * 2] & 2) != 0) {
        uVar5 = uVar5 - 0x20;
      }
    }
    else {
      if (iVar4 == 0) {
        return 0;
      }
      iVar4 = param_3 + -2;
      if (*param_2 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = (uint)CONCAT11(bVar1,*param_2);
        param_2 = pbVar2 + 2;
      }
    }
    if (uVar5 != uVar3) break;
    param_3 = iVar4;
    param_1 = pbVar6;
    pbVar2 = param_2;
    if (uVar3 == 0) {
      return 0;
    }
  }
  if (uVar5 <= uVar3) {
    return 1;
  }
  return 0xffffffff;
}

