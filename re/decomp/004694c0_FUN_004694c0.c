// FUN_004694c0 @ 004694c0 size=641 sig=undefined FUN_004694c0() cc=unknown
// callers: FUN_0046a844
// callees: FUN_004ae5d8,FUN_00462348,FUN_004693b0,FUN_0041e8d0,FUN_004879b0

void FUN_004694c0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint local_68;
  uint local_64;
  int local_60;
  int local_5c;
  char *local_4c;
  char *local_24;
  undefined *local_20;
  undefined *local_1c;
  undefined *local_18;
  undefined4 *local_14;
  
  local_5c = 0;
  local_14 = &DAT_004d561c;
  local_18 = &DAT_004d5748;
  local_1c = &DAT_004d56bc;
  local_20 = &DAT_004d5630;
  do {
    local_24 = &DAT_005a0555;
    for (local_64 = 0; (int)local_64 < (int)DAT_004d5b1b; local_64 = local_64 + 1) {
      if ((local_64 & 1) == 0) {
        iVar2 = FUN_00462348();
        if (iVar2 != 0) {
          return;
        }
        FUN_0041e8d0((int)(local_64 * 10) / (int)DAT_004d5b1b + (local_5c * 0x32) / 5 + 0x32);
      }
      local_4c = local_24;
      for (local_68 = 0; (int)local_68 < (int)DAT_004d5b1a; local_68 = local_68 + 1) {
        if ((local_68 & 0xf) == 0) {
          FUN_004879b0();
        }
        iVar3 = (int)*local_4c;
        iVar9 = 0;
        iVar2 = *(int *)(local_20 + iVar3 * 0x14);
        uVar1 = *(uint *)(local_18 + iVar3 * 0x14);
        uVar8 = *(uint *)(local_1c + iVar3 * 0x14);
        do {
          uVar4 = FUN_004ae5d8();
          uVar4 = uVar4 & 0x80000001;
          if ((int)uVar4 < 0) {
            uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
          }
          if (uVar4 != 0) break;
          iVar2 = iVar2 >> 1;
          if (iVar2 == 0) {
            iVar2 = 1;
          }
          uVar8 = uVar8 * 2;
          iVar9 = iVar9 + 1;
        } while (iVar9 < 2);
        local_60 = 0;
        if (0 < iVar2) {
          do {
            uVar4 = FUN_004ae5d8();
            uVar4 = uVar4 & 0x8000003f;
            if ((int)uVar4 < 0) {
              uVar4 = (uVar4 - 1 | 0xffffffc0) + 1;
            }
            uVar5 = FUN_004ae5d8();
            uVar5 = uVar5 & 0x8000003f;
            if ((int)uVar5 < 0) {
              uVar5 = (uVar5 - 1 | 0xffffffc0) + 1;
            }
            iVar9 = (int)uVar8 >> 1;
            iVar3 = iVar9;
            if (iVar9 < 0) {
              iVar3 = iVar9 + (uint)((uVar8 & 1) != 0);
            }
            if (iVar3 == 0) {
              iVar6 = 0;
            }
            else {
              iVar6 = FUN_004ae5d8();
              iVar6 = iVar6 % iVar3;
            }
            if (iVar9 < 0) {
              iVar9 = iVar9 + (uint)((uVar8 & 1) != 0);
            }
            iVar10 = (int)uVar1 >> 1;
            iVar3 = iVar10;
            if (iVar10 < 0) {
              iVar3 = iVar10 + (uint)((uVar1 & 1) != 0);
            }
            if (iVar3 == 0) {
              iVar7 = 0;
            }
            else {
              iVar7 = FUN_004ae5d8();
              iVar7 = iVar7 % iVar3;
            }
            if (iVar10 < 0) {
              iVar10 = iVar10 + (uint)((uVar1 & 1) != 0);
            }
            FUN_004693b0(uVar4 + local_68 * 0x20 + -0x10,uVar5 + local_64 * 0x20 + -0x10,*local_14,
                         iVar6 + iVar9,iVar7 + iVar10);
            local_60 = local_60 + 1;
          } while (local_60 < iVar2);
        }
        local_4c = local_4c + 10;
      }
      local_24 = local_24 + 400;
    }
    local_5c = local_5c + 1;
    local_14 = local_14 + 1;
    local_18 = local_18 + 4;
    local_1c = local_1c + 4;
    local_20 = local_20 + 4;
    if (4 < local_5c) {
      return;
    }
  } while( true );
}

