// FUN_00474c08 @ 00474c08 size=185 sig=undefined FUN_00474c08() cc=unknown
// callers: 
// callees: FUN_004749f8

undefined4 FUN_00474c08(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  byte bVar3;
  byte *pbVar4;
  byte bVar5;
  int iVar6;
  
  if (DAT_004d5aec < 7) {
    bVar1 = 0xff;
    pbVar4 = &DAT_0059f162;
    for (iVar6 = 0; iVar6 < DAT_004d5aec; iVar6 = iVar6 + 1) {
      bVar1 = bVar1 ^ '\x01' << (*pbVar4 & 0x1f);
      pbVar4 = pbVar4 + 0x2d8;
    }
    if ((&DAT_0059f162)[param_1 * 0x2d8] == '\0') {
      bVar3 = 6;
    }
    else {
      bVar3 = (&DAT_0059f162)[param_1 * 0x2d8] - 1;
    }
    for (bVar5 = (&DAT_0059f162)[param_1 * 0x2d8]; bVar3 != bVar5; bVar5 = bVar5 + 1) {
      if (bVar5 == 7) {
        bVar5 = 0;
      }
      if ((1 << (bVar5 & 0x1f) & (uint)bVar1) != 0) break;
    }
    uVar2 = FUN_004749f8(param_1,bVar5,0xffffffff);
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}

