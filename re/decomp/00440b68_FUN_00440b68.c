// FUN_00440b68 @ 00440b68 size=1020 sig=undefined FUN_00440b68() cc=unknown
// callers: FUN_0044a000,FUN_00449dec
// callees: FUN_0043febc,FUN_0047e054,FUN_00459bdc,FUN_0049b268,FUN_00440b34,FUN_00463d00,FUN_0045a6e4,FUN_0044081c,FUN_00464620,FUN_0048d2e7,FUN_0043e694,FUN_00463da8,FUN_0045a50c,FUN_00440694,FUN_0043f858,FUN_0043ee90,FUN_0048d32c,FUN_0045a8a4,FUN_0048463c,FUN_0045a3e4

void FUN_00440b68(void)

{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  bool bVar10;
  int local_3c [3];
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  uint local_1c;
  int local_18;
  int local_14;
  
  FUN_00463da8(1);
  FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
  uVar2 = 1;
  if (*(short *)(DAT_0051bddc + 0x26) != 2) {
    uVar2 = 2;
  }
  FUN_0049b268(DAT_0058df44,uVar2);
  FUN_00464620(DAT_004c5458,DAT_004c545c,DAT_00559df8,DAT_00559dfc,0,1);
  piVar3 = local_3c;
  local_3c[0] = 0;
  if (-1 < DAT_004c5458) {
    piVar3 = &DAT_004c5458;
  }
  DAT_00559de8 = *piVar3;
  local_3c[1] = 0;
  if (DAT_004c545c < 0) {
    piVar3 = local_3c + 1;
  }
  else {
    piVar3 = &DAT_004c545c;
  }
  DAT_00559dec = *piVar3;
  local_3c[2] = DAT_004c5458 + DAT_00559df8 + -1;
  if (DAT_00583e0c < local_3c[2]) {
    piVar3 = &DAT_00583e0c;
  }
  else {
    piVar3 = local_3c + 2;
  }
  DAT_00559df0 = *piVar3;
  local_30 = DAT_004c545c + DAT_00559dfc + -1;
  if (DAT_00583e10 < local_30) {
    piVar3 = &DAT_00583e10;
  }
  else {
    piVar3 = &local_30;
  }
  DAT_00559df4 = *piVar3;
  FUN_00463d00(DAT_004c5458,DAT_004c545c,DAT_00559df8,DAT_00559dfc);
  FUN_0047e054(DAT_00559df4);
  uVar1 = DAT_004c4a58;
  iVar4 = DAT_00559dfc;
  if (DAT_00559dfc < 0) {
    iVar4 = DAT_00559dfc + 0x1f;
  }
  iVar4 = (iVar4 >> 5) + DAT_004c4a5c;
  uVar6 = DAT_004c4a58;
  if ((int)DAT_004c4a58 < 0) {
    uVar6 = DAT_004c4a58 - 1;
  }
  iVar5 = (int)uVar6 >> 1;
  if (iVar5 < 0) {
    iVar5 = iVar5 + (uint)((uVar6 & 1) != 0);
  }
  local_2c = iVar5 + iVar4;
  local_28 = (iVar4 - iVar5) + -1;
  local_24 = FUN_00440b34();
  bVar10 = (uVar1 & 1) == 0;
  local_20 = DAT_00559de8;
  if (!bVar10) {
    local_20 = DAT_00559de8 + -0x20;
  }
  local_1c = (uint)bVar10;
  for (local_18 = DAT_00559df4; DAT_00559dec + -0x10 <= local_18; local_18 = local_18 + -0x10) {
    local_14 = local_2c;
    iVar7 = local_28 * DAT_0058f140 * 0x20 + DAT_0058f140 * 0x1f + local_2c * 0x20;
    iVar5 = local_20;
    for (iVar4 = local_28; ((iVar5 < DAT_00559df0 && (local_14 < DAT_004d5b1a)) && (-1 < iVar4));
        iVar4 = iVar4 + -1) {
      if ((iVar4 < DAT_004d5b1b) && (-1 < local_14)) {
        iVar9 = iVar4 * 400 + local_14 * 10;
        if ((*(byte *)(&DAT_005a43ec + (short)(&DAT_005a0552)[local_14 * 5 + iVar4 * 200] * 0x2b7) &
            3) == 0) {
          if ((&DAT_005a0556)[iVar9] == '\0') {
            FUN_0043e694(iVar5,local_18,DAT_0058f134 + iVar7,DAT_0058f138 + iVar7);
          }
          else {
            FUN_0043ee90(iVar5,local_18,DAT_0058f134 + iVar7,DAT_0058f138 + iVar7,
                         (int)(char)(&DAT_005a0556)[iVar9],local_24);
          }
        }
        else if ((&DAT_005a0556)[iVar9] == '\0') {
          FUN_0043f858(iVar5,local_18,DAT_0058f134 + iVar7,DAT_0058f138 + iVar7,2);
        }
        else {
          FUN_0043febc(iVar5,local_18,DAT_0058f134 + iVar7,DAT_0058f138 + iVar7,2,
                       (int)(char)(&DAT_005a0556)[iVar9],local_24);
        }
        if ((DAT_004d5ad4 != 0) && ((&DAT_005a0554)[iVar9] != '\0')) {
          FUN_00440694(iVar5,local_18,(int)(char)(&DAT_005a0554)[iVar9],iVar7);
        }
      }
      iVar5 = iVar5 + 0x40;
      local_14 = local_14 + 1;
      iVar7 = iVar7 - (DAT_0058f140 * 0x20 + -0x20);
    }
    if (local_1c == 0) {
      local_28 = local_28 + -1;
      local_20 = local_20 + 0x20;
    }
    else {
      local_2c = local_2c + -1;
      local_20 = local_20 + -0x20;
    }
    local_1c = local_1c ^ 1;
  }
  FUN_0048463c(0);
  for (puVar8 = &DAT_005a4eac; puVar8 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar8 = puVar8 + 0x2b7) {
    if ((*(char *)((int)puVar8 + 0x7e) != '\0') && ((*(byte *)((int)puVar8 + 0x1d) & 1) == 0)) {
      FUN_0045a8a4(puVar8);
      if (DAT_004d59b0 == 0) {
        FUN_00459bdc(puVar8);
      }
      else if ('\x01' < *(char *)((int)puVar8 + DAT_0058f1f4 + 0x66)) {
        FUN_0045a6e4(puVar8);
      }
      FUN_0044081c(puVar8);
      FUN_0045a50c(puVar8);
      FUN_0045a3e4(puVar8);
    }
  }
  FUN_0048463c(DAT_0058f1d0);
  FUN_0048d32c();
  return;
}

