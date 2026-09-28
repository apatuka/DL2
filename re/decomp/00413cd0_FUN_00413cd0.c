// FUN_00413cd0 @ 00413cd0 size=410 sig=undefined FUN_00413cd0() cc=unknown
// callers: FUN_00413fe4
// callees: FUN_00414f04,FUN_00413980,FUN_004a3de6,FUN_004a60b1,FUN_0049eb44,FUN_004a2004,FUN_004493dc

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00413cd0(void)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  
  DAT_004b7028 = FUN_004a3de6(0,0x32323944);
  if (DAT_004b7028 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005331f8 = DAT_004d59b4;
    DAT_004d59b4 = 0x59;
    FUN_00414f04(DAT_004b7028);
    local_94 = DAT_004b7030;
    local_90 = DAT_004b702c;
    local_8c = DAT_004b7038;
    local_88 = DAT_004b7034;
    FUN_004a60b1(&local_94,0);
    FUN_004a2004(DAT_004b7028);
    DAT_005331fc = *(undefined2 *)(DAT_006534c0 + 8);
    DAT_005331fe = *(undefined2 *)(DAT_006534c0 + 10);
    DAT_00533200 = *(undefined2 *)(DAT_006534c0 + 6);
    DAT_00533202 = *(undefined2 *)(DAT_006534c0 + 0xc);
    DAT_00533204 = *(undefined2 *)(DAT_006534c0 + 0xe);
    _DAT_00533206 = (short)*(char *)(DAT_006534c0 + 4);
    DAT_00533208 = *(undefined2 *)(DAT_006534c0 + 2);
    iVar3 = 0;
    do {
      FUN_00413980(iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
    if (*(char *)(DAT_006534c0 + 4) == '\0') {
      FUN_0049eb44(DAT_004b7028,0x13,1,0xb,1,0);
    }
    else {
      FUN_0049eb44(DAT_004b7028,0x11,1,0xb,1,0);
    }
    uVar1 = *(ushort *)(DAT_006534c0 + 2) & 0xff;
    if (uVar1 == 0xff) {
      uVar1 = 6;
    }
    switch(uVar1) {
    case 0:
      uVar2 = 0x16;
      break;
    case 1:
      uVar2 = 0x1e;
      break;
    case 2:
      uVar2 = 0x18;
      break;
    case 3:
      uVar2 = 0x1a;
      break;
    case 4:
      uVar2 = 0x1c;
      break;
    default:
      uVar2 = 0x22;
      break;
    case 6:
      uVar2 = 0x20;
    }
    FUN_0049eb44(DAT_004b7028,uVar2,1,0xb,1,0);
    uVar2 = 1;
  }
  return uVar2;
}

