// FUN_00441fa4 @ 00441fa4 size=480 sig=undefined FUN_00441fa4() cc=unknown
// callers: FUN_00442184
// callees: memset,FUN_0045dfb0

void FUN_00441fa4(int param_1)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  ushort uVar4;
  short *local_2c;
  ushort *local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined2 *local_c;
  undefined4 *local_8;
  
  local_10 = 0;
  local_c = &DAT_0055dc60;
  local_2c = &DAT_0055dc74;
  do {
    bVar2 = (byte)param_1;
    FUN_0045dfb0(0x2000 << (bVar2 & 0x1f));
    local_c[0xb] = 0;
    local_c[0xc] = 0;
    local_c[10] = 0;
    memset(local_c + 0x13,0,0xe);
    memset(local_c + 0xd,0,0xc);
    for (local_8 = &DAT_005a4eac; local_8 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        local_8 = local_8 + 0x2b7) {
      if (*(char *)(local_8 + 0x26d) == local_10) {
        local_14 = 0;
        local_1c = (ushort *)(local_8 + 0x224);
        do {
          uVar4 = *local_1c;
          for (local_18 = 0; (uVar4 != 0 && (local_18 < 0x10)); local_18 = local_18 + 1) {
            if ((uVar4 & 1) != 0) {
              iVar3 = local_14 * 0x10 + local_18;
              iVar1 = iVar3 * 0xadc;
              local_c[(iVar3 >> 4) + 0x13] = local_c[(iVar3 >> 4) + 0x13] | 1 << ((byte)iVar3 & 0xf)
              ;
              if (((char)(&DAT_005a4d84)[iVar1] != local_10) &&
                 ((0x2000 << (bVar2 & 0x1f) & (&DAT_005a43ec)[iVar3 * 0x2b7]) == 0)) {
                if ((&DAT_005a43f0)[iVar1] == -1) {
                  if ((&DAT_005a43f1)[iVar1] != '\0') {
                    *local_2c = *local_2c + 1;
                  }
                }
                else if ((char)(&DAT_005a43f0)[iVar1] != param_1) {
                  local_2c[1] = local_2c[1] + 1;
                  local_2c[2] = local_2c[2] | 1 << ((&DAT_005a43f0)[iVar1] & 0x1f);
                }
                (&DAT_005a43ec)[iVar3 * 0x2b7] =
                     (&DAT_005a43ec)[iVar3 * 0x2b7] | 0x2000 << (bVar2 & 0x1f);
              }
            }
            uVar4 = (short)uVar4 >> 1;
          }
          local_14 = local_14 + 1;
          local_1c = local_1c + 1;
        } while (local_14 < 7);
      }
    }
    local_2c = local_2c + 0x3d;
    local_10 = local_10 + 1;
    local_c = local_c + 0x3d;
  } while (local_10 < 0x20);
  FUN_0045dfb0(0x2000 << (bVar2 & 0x1f));
  return;
}

