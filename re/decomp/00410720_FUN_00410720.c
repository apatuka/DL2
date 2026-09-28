// FUN_00410720 @ 00410720 size=204 sig=undefined FUN_00410720() cc=unknown
// callers: FUN_00410870,FUN_0040ec50
// callees: FUN_0044d1a4

undefined * FUN_00410720(int param_1,undefined *param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  ushort *local_c;
  int local_8;
  
  if ((param_2[0x21] == '\0') || (param_2[0x20] != *(char *)(param_1 + 8))) {
    if ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x02') {
      local_c = (ushort *)(param_2 + 0x890);
      local_8 = 0;
      do {
        uVar3 = *local_c;
        for (iVar1 = 0; (uVar3 != 0 && (iVar1 < 0x10)); iVar1 = iVar1 + 1) {
          if ((uVar3 & 1) != 0) {
            iVar4 = (local_8 * 0x10 + iVar1) * 0xadc;
            if ((((&DAT_005a43f1)[iVar4] != '\0') &&
                ((&DAT_005a43f0)[iVar4] == *(char *)(param_1 + 8))) &&
               (iVar2 = FUN_0044d1a4(&DAT_005a43d0 + iVar4,0xf,0), iVar2 != -1)) {
              return &DAT_005a43d0 + iVar4;
            }
          }
          uVar3 = (short)uVar3 >> 1;
        }
        local_8 = local_8 + 1;
        local_c = local_c + 1;
      } while (local_8 < 7);
    }
  }
  else {
    iVar1 = FUN_0044d1a4(param_2,0xf,0);
    if (iVar1 != -1) {
      return param_2;
    }
  }
  return (undefined *)0x0;
}

