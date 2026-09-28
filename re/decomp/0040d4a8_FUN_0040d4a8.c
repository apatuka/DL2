// FUN_0040d4a8 @ 0040d4a8 size=280 sig=undefined FUN_0040d4a8() cc=unknown
// callers: FUN_004105e8,FUN_0040f700
// callees: 

undefined * FUN_0040d4a8(undefined *param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *local_18;
  uint local_14;
  int local_10;
  undefined *local_c;
  int local_8;
  
  if (param_2 == -1) {
    local_8 = 0x20;
  }
  else {
    local_8 = (int)(char)(&DAT_005a43f2)[param_2 * 0xadc];
  }
  local_c = (undefined *)0x0;
  local_10 = -1000000;
  if ((local_8 < 0) || (0x1f < local_8)) {
    local_14 = 0xffff;
  }
  else {
    local_14 = *(uint *)((int)&DAT_0055a828 + local_8 * 0x1a2);
  }
  iVar5 = 0;
  local_18 = (ushort *)(param_1 + 0x890);
  do {
    uVar1 = *local_18;
    for (iVar4 = 0; (uVar1 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
      if ((uVar1 & 1) != 0) {
        iVar2 = iVar5 * 0x10 + iVar4;
        iVar3 = iVar2 * 0xadc;
        if (((((&DAT_005a43f1)[iVar3] == '\0') && ((&DAT_005a4e28)[iVar2 * 0x2b7] == 0)) &&
            (((1 << ((&DAT_005a43f2)[iVar3] & 0x1f) & local_14) != 0 ||
             ((char)(&DAT_005a43f2)[iVar3] == local_8)))) &&
           (local_10 < (int)(&DAT_005a4de2)[iVar2 * 0x2b7])) {
          local_10 = (&DAT_005a4de2)[iVar2 * 0x2b7];
          local_c = &DAT_005a43d0 + iVar3;
        }
      }
      uVar1 = (short)uVar1 >> 1;
    }
    iVar5 = iVar5 + 1;
    local_18 = local_18 + 1;
  } while (iVar5 < 7);
  if (param_1[0x21] == '\0') {
    local_c = param_1;
  }
  return local_c;
}

