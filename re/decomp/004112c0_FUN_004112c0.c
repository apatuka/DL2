// FUN_004112c0 @ 004112c0 size=331 sig=undefined FUN_004112c0() cc=unknown
// callers: FUN_0041161c
// callees: FUN_00410e74,FUN_004ac65c

void FUN_004112c0(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  uint local_10;
  int local_c;
  int local_8;
  
  while (iVar2 = FUN_00410e74(&local_10,&local_c,&local_8), uVar5 = DAT_005331a2, iVar2 != 0) {
    if ((int)local_10 < 0) {
      DAT_005331e0 = DAT_005331e0 + local_c;
      uVar5 = DAT_005331a2 - local_8;
      while (iVar2 = local_c + -1, bVar6 = local_c != 0, local_c = iVar2, bVar6) {
        uVar4 = uVar5 & 0x3fff;
        uVar3 = DAT_005331a2 & 0x3fff;
        uVar5 = uVar5 + 1;
        bVar1 = *(byte *)(DAT_0053319e + uVar4);
        local_10 = (uint)bVar1;
        DAT_005331a2 = DAT_005331a2 + 1;
        *(byte *)(DAT_0053319e + uVar3) = bVar1;
        if (DAT_005331c0 == 0) {
          *(byte *)(DAT_005331c8 + DAT_005331cc) = bVar1;
          DAT_005331cc = DAT_005331cc + 1;
        }
        else {
          FUN_004ac65c(local_10,DAT_005331c0);
        }
      }
    }
    else {
      DAT_005331e0 = DAT_005331e0 + 1;
      DAT_005331a2 = DAT_005331a2 + 1;
      *(undefined1 *)(DAT_0053319e + (uVar5 & 0x3fff)) = (undefined1)local_10;
      if (DAT_005331c0 == 0) {
        *(undefined1 *)(DAT_005331c8 + DAT_005331cc) = (undefined1)local_10;
        DAT_005331cc = DAT_005331cc + 1;
      }
      else {
        FUN_004ac65c(local_10,DAT_005331c0);
      }
    }
    if (DAT_005331e0 < 0x4000) {
      for (; DAT_005331d8 <= DAT_005331e0; DAT_005331d8 = DAT_005331d8 << 1) {
        DAT_005331d4 = DAT_005331d4 + 1;
      }
    }
  }
  return;
}

