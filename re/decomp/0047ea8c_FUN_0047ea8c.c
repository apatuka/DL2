// FUN_0047ea8c @ 0047ea8c size=710 sig=undefined FUN_0047ea8c() cc=unknown
// callers: 
// callees: 

void FUN_0047ea8c(void)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  byte bVar12;
  byte bVar13;
  uint uVar14;
  byte bVar15;
  byte *local_24;
  int local_20;
  byte *local_1c;
  byte *local_18;
  int local_14;
  
  iVar9 = *DAT_00583e08 + DAT_00583e04;
  local_24 = (byte *)(iVar9 + DAT_00583e14);
  bVar8 = *(byte *)(iVar9 + 2) & 0xf8;
  bVar3 = *(byte *)(iVar9 + 1) & 0xf8;
  bVar13 = local_24[2] & 0xf8;
  bVar5 = local_24[1] & 0xf8;
  for (local_20 = 0; local_20 < DAT_00583e10 + -2; local_20 = local_20 + 1) {
    local_18 = local_24 + (1 - DAT_00583e14);
    pbVar1 = local_24 + DAT_00583e14;
    bVar2 = bVar3;
    bVar7 = bVar13;
    bVar12 = pbVar1[1] & 0xf8;
    bVar4 = *pbVar1 & 0xf8;
    bVar3 = bVar5;
    bVar5 = bVar8;
    for (local_14 = 1; bVar13 = bVar12, bVar8 = bVar7, local_1c = local_24 + 1,
        local_14 < DAT_00583e0c + -2; local_14 = local_14 + 1) {
      local_18 = local_18 + 1;
      bVar6 = *local_18 & 0xf8;
      bVar7 = local_18[DAT_00583e14] & 0xf8;
      bVar12 = local_18[DAT_00583e14 * 2] & 0xf8;
      if (((bVar8 == 0x40) || (bVar8 == 0x10)) || (bVar8 == 0x20)) {
        bVar15 = bVar8 != bVar2;
        if (bVar8 != bVar5) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar6) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar3) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar7) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar4) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar13) {
          bVar15 = bVar15 + 1;
        }
        if (bVar8 != bVar12) {
          bVar15 = bVar15 + 1;
        }
        if (4 < bVar15) {
          *local_1c = *local_1c & 7;
          *local_1c = *local_1c | bVar2;
        }
      }
      else {
        uVar10 = 0;
        uVar11 = 0;
        uVar14 = 0;
        if (bVar2 == 0x40) {
          uVar11 = 1;
        }
        else if (bVar2 == 0x10) {
          uVar10 = 1;
        }
        else if (bVar2 == 0x20) {
          uVar14 = 1;
        }
        if (bVar5 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar5 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar5 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar6 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar6 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar6 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar3 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar3 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar3 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar7 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar7 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar7 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar4 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar4 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar4 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar13 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar13 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar13 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (bVar12 == 0x40) {
          uVar11 = uVar11 + 1;
        }
        else if (bVar12 == 0x10) {
          uVar10 = uVar10 + 1;
        }
        else if (bVar12 == 0x20) {
          uVar14 = uVar14 + 1;
        }
        if (uVar11 < 5) {
          if (uVar10 < 5) {
            if (4 < uVar14) {
              *local_1c = *local_1c & 7;
              *local_1c = *local_1c | 0x20;
            }
          }
          else {
            *local_1c = *local_1c & 7;
            *local_1c = *local_1c | 0x10;
          }
        }
        else {
          *local_1c = *local_1c & 7;
          *local_1c = *local_1c | 0x40;
        }
      }
      local_24 = local_1c;
      bVar2 = bVar5;
      bVar4 = bVar13;
      bVar3 = bVar8;
      bVar5 = bVar6;
    }
    local_24 = pbVar1;
    bVar5 = bVar4;
  }
  return;
}

