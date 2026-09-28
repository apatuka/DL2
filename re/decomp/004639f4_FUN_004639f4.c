// FUN_004639f4 @ 004639f4 size=127 sig=undefined FUN_004639f4() cc=unknown
// callers: FUN_00463a74
// callees: FUN_00491d38,FUN_0048f774,FUN_00498ba9

void FUN_004639f4(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (DAT_0058df44 == 0) {
    DAT_0058df44 = FUN_00498ba9(0x408);
    if (DAT_0058df44 != 0) {
      FUN_0048f774(DAT_0058df44,0x408,0);
      *(undefined2 *)(DAT_0058df44 + 2) = 0x100;
    }
  }
  puVar2 = &DAT_0051a8a6;
  for (iVar3 = 0; iVar1 = DAT_0058df44, iVar3 < *(short *)(DAT_0058df44 + 2); iVar3 = iVar3 + 1) {
    *(undefined1 *)(DAT_0058df44 + 8 + iVar3 * 4) = *puVar2;
    *(undefined1 *)(iVar1 + 9 + iVar3 * 4) = puVar2[-1];
    *(undefined1 *)(iVar1 + 10 + iVar3 * 4) = puVar2[-2];
    puVar2 = puVar2 + 4;
  }
  *(ushort *)(DAT_0058df44 + 6) = *(ushort *)(DAT_0058df44 + 6) & 0xfff0;
  FUN_00491d38(DAT_0058df44);
  return;
}

