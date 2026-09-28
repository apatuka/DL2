// FUN_00462994 @ 00462994 size=799 sig=undefined FUN_00462994() cc=unknown
// callers: FUN_004634a0
// callees: FUN_004ae5d8,FUN_00462348,FUN_00462864,FUN_00462914

void FUN_00462994(void)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  short *psVar9;
  int local_24;
  int local_1c;
  short *local_18;
  short *local_14;
  
  for (local_1c = 0;
      (int)DAT_004d5b1a * (int)DAT_004d5b1b - local_1c != 0 &&
      local_1c <= (int)DAT_004d5b1a * (int)DAT_004d5b1b; local_1c = local_1c + 1) {
    iVar6 = FUN_00462348();
    if (iVar6 != 0) {
      return;
    }
    iVar6 = (int)DAT_004d5b1a;
    if (iVar6 == 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = FUN_004ae5d8();
      iVar8 = iVar8 % iVar6;
    }
    iVar6 = (int)DAT_004d5b1b;
    if (iVar6 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_004ae5d8();
      iVar3 = iVar3 % iVar6;
    }
    if ((&DAT_005a0552)[iVar3 * 200 + iVar8 * 5] == -1) {
      uVar4 = FUN_004ae5d8();
      uVar4 = uVar4 & 0x80000003;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
      }
      iVar6 = 0;
      do {
        uVar5 = iVar6 + uVar4 & 0x80000003;
        if ((int)uVar5 < 0) {
          uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
        }
        sVar2 = FUN_00462864(iVar8,iVar3,uVar5);
      } while ((sVar2 == -1) && (iVar6 = iVar6 + 1, iVar6 < 4));
      if (sVar2 != -1) {
        (&DAT_005a0552)[iVar3 * 200 + iVar8 * 5] = sVar2;
        (&DAT_005a444e)[sVar2 * 0xadc] = (&DAT_005a444e)[sVar2 * 0xadc] + '\x01';
      }
    }
  }
  local_1c = 0;
  bVar1 = false;
  while ((local_1c < 0x14 && (!bVar1))) {
    iVar6 = FUN_00462348();
    if (iVar6 != 0) {
      return;
    }
    bVar1 = true;
    local_14 = &DAT_005a0552;
    for (local_24 = 0; local_24 < DAT_004d5b1b; local_24 = local_24 + 1) {
      local_18 = local_14;
      for (iVar6 = 0; iVar6 < DAT_004d5b1a; iVar6 = iVar6 + 1) {
        if (*local_18 == -1) {
          bVar1 = false;
          uVar4 = FUN_004ae5d8();
          uVar4 = uVar4 & 0x80000003;
          if ((int)uVar4 < 0) {
            uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
          }
          iVar8 = 0;
          do {
            uVar5 = iVar8 + uVar4 & 0x80000003;
            if ((int)uVar5 < 0) {
              uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
            }
            sVar2 = FUN_00462914(iVar6,local_24,uVar5);
          } while ((sVar2 == -1) && (iVar8 = iVar8 + 1, iVar8 < 4));
          if (sVar2 != -1) {
            *local_18 = sVar2;
            (&DAT_005a444e)[sVar2 * 0xadc] = (&DAT_005a444e)[sVar2 * 0xadc] + '\x01';
          }
        }
        local_18 = local_18 + 5;
      }
      local_14 = local_14 + 200;
    }
    local_1c = local_1c + 1;
  }
  if (!bVar1) {
    psVar9 = &DAT_005a0552;
    (&DAT_005a444e)[DAT_004d5b18 * 0xadc] = 0;
    local_24 = 0;
    while ((local_24 < DAT_004d5b1b && (iVar6 = FUN_00462348(), iVar6 == 0))) {
      psVar7 = psVar9;
      for (iVar6 = 0; iVar6 < DAT_004d5b1a; iVar6 = iVar6 + 1) {
        if (*psVar7 == -1) {
          if ((&DAT_005a444e)[DAT_004d5b18 * 0xadc] == '0') {
            DAT_004d5b18 = DAT_004d5b18 + 1;
            (&DAT_005a444e)[DAT_004d5b18 * 0xadc] = 0;
          }
          *psVar7 = DAT_004d5b18;
          (&DAT_005a444e)[DAT_004d5b18 * 0xadc] = (&DAT_005a444e)[DAT_004d5b18 * 0xadc] + '\x01';
        }
        psVar7 = psVar7 + 5;
      }
      local_24 = local_24 + 1;
      psVar9 = psVar9 + 200;
    }
  }
  return;
}

