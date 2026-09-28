// FUN_00469744 @ 00469744 size=998 sig=undefined FUN_00469744() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8,FUN_00462348,FUN_0041e8d0,FUN_004879b0

void FUN_00469744(void)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined *local_34;
  short *local_30;
  undefined4 local_2c;
  int local_28;
  int local_24 [3];
  char *local_18;
  char *local_14;
  char *local_10;
  
  iVar2 = DAT_0058f138;
  local_38 = DAT_0058f138;
  local_14 = &DAT_005a0555;
  for (local_44 = 0; (int)local_44 < (int)DAT_004d5b1b; local_44 = local_44 + 1) {
    local_18 = local_14;
    for (local_48 = 0; (int)local_48 < (int)DAT_004d5b1a; local_48 = local_48 + 1) {
      uVar1 = *(undefined4 *)(&DAT_004d553c + *local_18 * 0x20);
      for (iVar8 = local_44 << 5; iVar8 < (int)(local_44 * 0x20 + 0x20); iVar8 = iVar8 + 1) {
        for (local_6c = local_48 << 5; local_6c < (int)(local_48 * 0x20 + 0x20);
            local_6c = local_6c + 1) {
          *(short *)(iVar2 + (iVar8 * DAT_0058f140 + local_6c) * 2) = (short)uVar1;
        }
      }
      local_18 = local_18 + 10;
    }
    local_14 = local_14 + 400;
  }
  local_44 = 0;
  local_14 = &DAT_005a0555;
  do {
    if ((int)DAT_004d5b1b <= (int)local_44) {
      return;
    }
    if ((local_44 & 1) == 0) {
      iVar2 = FUN_00462348();
      if (iVar2 != 0) {
        return;
      }
      FUN_0041e8d0((int)(local_44 * 0x32) / (int)DAT_004d5b1b);
    }
    local_10 = local_14;
    for (local_48 = 0; (int)local_48 < (int)DAT_004d5b1a; local_48 = local_48 + 1) {
      if ((local_48 & 0xf) == 0) {
        FUN_004879b0();
      }
      iVar2 = *local_10 * 0x20;
      local_58 = *(int *)(&DAT_004d5540 + iVar2);
      local_54 = *(int *)(&DAT_004d554c + iVar2);
      local_50 = *(int *)(&DAT_004d5550 + iVar2);
      local_34 = (&PTR_DAT_004d5558)[*local_10 * 8];
      local_4c = *(int *)(&DAT_004d5554 + iVar2);
      local_60 = 0;
      if (0 < local_58) {
        do {
          iVar2 = FUN_004ae5d8();
          iVar8 = iVar2 % 0x1f + local_48 * 0x20;
          iVar2 = FUN_004ae5d8();
          iVar2 = iVar2 % 0x1f + local_44 * 0x20;
          uVar3 = FUN_004ae5d8();
          uVar3 = uVar3 & 0x8000003f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xffffffc0) + 1;
          }
          local_68 = *(short *)(local_34 + uVar3 * 2) * 8;
          if (local_68 < 0) {
            local_2c = 0xffffffff;
            local_68 = *(short *)(local_34 + uVar3 * 2) * -8;
          }
          else {
            local_2c = 1;
          }
          uVar3 = FUN_004ae5d8();
          uVar3 = uVar3 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          local_40 = uVar3 + local_54;
          if (local_50 < (int)(uVar3 + local_54)) {
            local_40 = local_50;
          }
          iVar4 = local_68;
          if (local_68 < 0) {
            iVar4 = local_68 + 7;
          }
          local_3c = ((iVar4 >> 3) << 4) / local_40;
          local_28 = 0;
          local_24[0] = iVar8 - local_3c;
          if (iVar8 - local_3c < 1) {
            piVar6 = &local_28;
          }
          else {
            piVar6 = local_24;
          }
          for (local_64 = *piVar6; (local_64 < iVar8 + local_3c && (local_64 < DAT_0058f140));
              local_64 = local_64 + 1) {
            uVar3 = local_64 - iVar8 >> 0x1f;
            iVar4 = ((local_64 - iVar8 ^ uVar3) - uVar3) * 8;
            local_24[1] = 0;
            local_24[2] = iVar2 - local_3c;
            if (iVar2 - local_3c < 1) {
              piVar6 = local_24 + 1;
            }
            else {
              piVar6 = local_24 + 2;
            }
            iVar7 = *piVar6;
            local_30 = (short *)((iVar7 * DAT_0058f140 + local_64) * 2 + local_38);
            for (; (iVar7 < local_3c + iVar2 && (iVar7 < DAT_0058f13c)); iVar7 = iVar7 + 1) {
              uVar3 = iVar7 - iVar2 >> 0x1f;
              iVar5 = ((iVar7 - iVar2 ^ uVar3) - uVar3) * 8;
              if (iVar5 < iVar4) {
                iVar5 = ((iVar5 >> 1) + iVar4) * local_40;
                if (iVar5 < 0) {
                  iVar5 = iVar5 + 0xf;
                }
                local_5c = iVar5 >> 4;
              }
              else {
                iVar5 = (iVar5 + (iVar4 >> 1)) * local_40;
                if (iVar5 < 0) {
                  iVar5 = iVar5 + 0xf;
                }
                local_5c = iVar5 >> 4;
              }
              if (local_5c < local_68) {
                if (local_4c < local_5c) {
                  piVar6 = &local_5c;
                }
                else {
                  piVar6 = &local_4c;
                }
                *local_30 = *local_30 + ((short)local_68 - (short)*piVar6) * (short)local_2c;
              }
              local_30 = local_30 + DAT_0058f140;
            }
          }
          local_60 = local_60 + 1;
        } while (local_60 < local_58);
      }
      local_10 = local_10 + 10;
    }
    local_44 = local_44 + 1;
    local_14 = local_14 + 400;
  } while( true );
}

