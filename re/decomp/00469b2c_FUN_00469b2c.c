// FUN_00469b2c @ 00469b2c size=801 sig=undefined FUN_00469b2c() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8,FUN_00462348,FUN_0041e8d0,FUN_004879b0

void FUN_00469b2c(void)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_28;
  uint local_24;
  int local_20;
  int local_1c;
  uint local_18;
  
  local_18 = 0;
  do {
    if (DAT_0058f13c <= (int)local_18) {
      FUN_0041e8d0(100);
      return;
    }
    if ((local_18 & 0xf) == 0) {
      iVar5 = FUN_00462348();
      if (iVar5 != 0) {
        return;
      }
      FUN_0041e8d0((int)(local_18 * 100) / DAT_0058f13c);
    }
    FUN_004879b0();
    for (local_1c = 0; local_1c < DAT_0058f140; local_1c = local_1c + 1) {
      uVar6 = local_18;
      if ((int)local_18 < 0) {
        uVar6 = local_18 + 0x1f;
      }
      iVar5 = local_1c;
      if (local_1c < 0) {
        iVar5 = local_1c + 0x1f;
      }
      if (((((&DAT_005a0555)[(iVar5 >> 5) * 10 + ((int)uVar6 >> 5) * 400] != '\x06') ||
           (iVar5 = FUN_004ae5d8(), iVar5 % 300 == 0)) &&
          (*(short *)(DAT_0058f138 + (local_18 * DAT_0058f140 + local_1c) * 2) == 1)) &&
         (iVar5 = FUN_004ae5d8(), iVar5 % 0x28 == 0)) {
        iVar5 = (int)*(short *)(DAT_0058f138 + (local_18 * DAT_0058f140 + local_1c) * 2);
        iVar8 = local_1c;
        uVar6 = local_18;
        while (uVar4 = uVar6, iVar3 = iVar8, -1 < iVar5) {
          local_20 = 0;
          for (uVar6 = uVar4 - 1; (int)uVar6 <= (int)(uVar4 + 1); uVar6 = uVar6 + 1) {
            iVar8 = iVar3 + -1;
            iVar7 = DAT_0058f134 + iVar8;
            for (; iVar8 <= iVar3 + 1; iVar8 = iVar8 + 1) {
              if ((((iVar3 != iVar8) || (uVar4 != uVar6)) &&
                  ((-1 < iVar8 && ((-1 < (int)uVar6 && (iVar8 < DAT_0058f140)))))) &&
                 (((int)uVar6 < DAT_0058f13c &&
                  (((iVar9 = (int)*(short *)(DAT_0058f138 + (uVar6 * DAT_0058f140 + iVar8) * 2),
                    iVar5 + -2 < iVar9 && (local_20 <= iVar9)) &&
                   (((int)*(char *)(iVar7 + uVar6 * DAT_0058f140) & 0xf8U) != 0x40)))))) {
                local_28 = iVar8;
                local_24 = uVar6;
                local_20 = iVar9;
              }
              iVar7 = iVar7 + 1;
            }
          }
          if (local_20 == 0) break;
          pbVar1 = (byte *)(DAT_0058f134 + uVar4 * DAT_0058f140 + iVar3);
          *pbVar1 = *pbVar1 & 7;
          pbVar1 = (byte *)(DAT_0058f134 + uVar4 * DAT_0058f140 + iVar3);
          *pbVar1 = *pbVar1 | 0x40;
          if (iVar3 < DAT_0058f140 + -1) {
            pbVar1 = (byte *)(DAT_0058f134 + uVar4 * DAT_0058f140 + 1 + iVar3);
            *pbVar1 = *pbVar1 & 7;
            pbVar1 = (byte *)(DAT_0058f134 + uVar4 * DAT_0058f140 + 1 + iVar3);
            *pbVar1 = *pbVar1 | 0x40;
          }
          if ((int)uVar4 < DAT_0058f13c + -1) {
            pbVar1 = (byte *)(DAT_0058f134 + (uVar4 + 1) * DAT_0058f140 + iVar3);
            *pbVar1 = *pbVar1 & 7;
            pbVar1 = (byte *)(DAT_0058f134 + (uVar4 + 1) * DAT_0058f140 + iVar3);
            *pbVar1 = *pbVar1 | 0x40;
          }
          if ((iVar3 < DAT_0058f140 + -1) && ((int)uVar4 < DAT_0058f13c + -1)) {
            pbVar1 = (byte *)(DAT_0058f134 + (uVar4 + 1) * DAT_0058f140 + 1 + iVar3);
            *pbVar1 = *pbVar1 & 7;
            pbVar1 = (byte *)(DAT_0058f134 + (uVar4 + 1) * DAT_0058f140 + 1 + iVar3);
            *pbVar1 = *pbVar1 | 0x40;
          }
          iVar5 = local_20;
          iVar8 = local_28;
          uVar6 = local_24;
          if (iVar3 != 0) {
            bVar2 = *(byte *)(DAT_0058f134 + iVar3 + -1 + uVar4 * DAT_0058f140);
            iVar8 = ((int)(char)bVar2 & 7U) - 1;
            if (iVar8 < 0) {
              iVar8 = 0;
            }
            *(byte *)(DAT_0058f134 + iVar3 + -1 + uVar4 * DAT_0058f140) = bVar2 & 0xf8 | (byte)iVar8
            ;
            iVar8 = local_28;
            uVar6 = local_24;
          }
        }
      }
    }
    local_18 = local_18 + 1;
  } while( true );
}

