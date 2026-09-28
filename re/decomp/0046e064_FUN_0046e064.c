// FUN_0046e064 @ 0046e064 size=722 sig=undefined FUN_0046e064() cc=unknown
// callers: FUN_0046e338
// callees: FUN_0044d1e4,FUN_0046dfd8,FUN_004412d4,FUN_0046e004

byte FUN_0046e064(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  ushort uVar6;
  int iVar7;
  byte bVar8;
  ushort *local_28;
  ushort *local_24;
  int local_20;
  ushort local_1a;
  int local_18;
  int local_14;
  
  bVar1 = 0;
  local_14 = 0;
  do {
    if ((local_14 == param_2) || (iVar2 = FUN_004412d4(local_14,param_2,4), iVar2 != 0)) {
      iVar2 = FUN_0044d1e4(param_1,9,0);
      bVar8 = iVar2 != -1;
      bVar5 = (byte)local_14;
      if ((1 << (bVar5 & 0x1f) & *(uint *)(param_1 + 0x8b0)) != 0) {
        *(uint *)(param_1 + 0x8b0) = *(uint *)(param_1 + 0x8b0) | 1 << (bVar5 & 0x1f);
      }
      if ((*(char *)(param_1 + 0x20) == local_14) ||
         ((DAT_00583c20 != 0 && (local_14 == DAT_0058f1f4)))) {
        if (local_14 == param_2) {
          bVar8 = 4;
        }
        else {
          bVar8 = 3;
        }
      }
      else {
        uVar3 = 1 << (bVar5 & 0x1f);
        if ((((((int)DAT_004fc1ba & uVar3) != 0) && (((byte)DAT_004d5b24 & 1) == 0)) &&
            (((int)*(char *)(param_1 + 0x997) & uVar3) == 0)) ||
           ((*(short *)(&DAT_0055a0d8 + (char)(&DAT_0059f162)[local_14 * 0x2d8] * 2) != 0 ||
            ((DAT_004d63d8 == 1 && ((&DAT_0059f161)[local_14 * 0x2d8] == '\x01')))))) {
          bVar8 = 2;
        }
        iVar2 = FUN_0046dfd8(param_1,local_14);
        if (((iVar2 == 0) && ((DAT_004d63d8 != 2 || ((&DAT_0059f161)[local_14 * 0x2d8] != '\x01'))))
           && (DAT_004d5aa0 == '\0')) {
          local_18 = 0;
          local_24 = (ushort *)(param_1 + 0x890);
          do {
            local_1a = *local_24;
            local_20 = 0;
LAB_0046e2e5:
            if ((local_1a == 0) || (0xf < local_20)) goto LAB_0046e2f8;
            if ((local_1a & 1) == 0) {
LAB_0046e2de:
              local_20 = local_20 + 1;
              local_1a = (short)local_1a >> 1;
              goto LAB_0046e2e5;
            }
            iVar2 = local_18 * 0x10 + local_20;
            iVar7 = iVar2 * 0xadc;
            if ((((&DAT_005a444e)[iVar7] == '\0') ||
                ((*(byte *)((int)&DAT_005a43ec + iVar7 + 1) & 1) != 0)) ||
               (((char)(&DAT_005a43f0)[iVar7] != local_14 &&
                (iVar7 = FUN_0046dfd8(&DAT_005a43d0 + iVar7,local_14), iVar7 == 0)))) {
              iVar7 = 0;
              local_28 = &DAT_005a4c60 + iVar2 * 0x56e;
              do {
                iVar2 = 0;
                uVar6 = *local_28;
LAB_0046e2ca:
                if ((uVar6 == 0) || (0xf < iVar2)) goto LAB_0046e2d4;
                if ((uVar6 & 1) == 0) {
LAB_0046e2c6:
                  iVar2 = iVar2 + 1;
                  uVar6 = (short)uVar6 >> 1;
                  goto LAB_0046e2ca;
                }
                iVar4 = (iVar7 * 0x10 + iVar2) * 0xadc;
                if ((((&DAT_005a444e)[iVar4] == '\0') ||
                    ((*(byte *)((int)&DAT_005a43ec + iVar4 + 1) & 1) != 0)) ||
                   (iVar4 = FUN_0046e004(&DAT_005a43d0 + iVar4,local_14), iVar4 == 0))
                goto LAB_0046e2c6;
                bVar8 = 3;
LAB_0046e2d4:
                iVar7 = iVar7 + 1;
                local_28 = local_28 + 1;
              } while (iVar7 < 7);
              goto LAB_0046e2de;
            }
            bVar8 = 3;
LAB_0046e2f8:
            local_18 = local_18 + 1;
            local_24 = local_24 + 1;
          } while (local_18 < 7);
        }
        else {
          bVar8 = 3;
        }
      }
      if (bVar1 < bVar8) {
        bVar1 = bVar8;
      }
    }
    local_14 = local_14 + 1;
    if (6 < local_14) {
      return bVar1;
    }
  } while( true );
}

