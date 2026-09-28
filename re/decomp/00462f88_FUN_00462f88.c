// FUN_00462f88 @ 00462f88 size=140 sig=undefined FUN_00462f88() cc=unknown
// callers: FUN_00463014,FUN_00462f88
// callees: FUN_00462f88

void FUN_00462f88(int param_1)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  ushort *local_8;
  
  if ((0 < DAT_00583db0) && (*(char *)(param_1 + 0x21) != '\0')) {
    DAT_00583dac = DAT_00583dac + 1;
    DAT_00583db0 = DAT_00583db0 + -1;
    *(undefined1 *)(param_1 + 0x21) = 0;
    iVar4 = 0;
    local_8 = (ushort *)(param_1 + 0x890);
    do {
      uVar2 = *local_8;
      for (iVar3 = 0; ((0 < DAT_00583db0 && (uVar2 != 0)) && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
        if (((uVar2 & 1) != 0) &&
           (iVar1 = (iVar4 * 0x10 + iVar3) * 0xadc, (&DAT_005a43f1)[iVar1] != '\0')) {
          FUN_00462f88(&DAT_005a43d0 + iVar1);
        }
        uVar2 = (short)uVar2 >> 1;
      }
      iVar4 = iVar4 + 1;
      local_8 = local_8 + 1;
    } while (iVar4 < 7);
  }
  return;
}

