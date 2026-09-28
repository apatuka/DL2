// FUN_0040d920 @ 0040d920 size=110 sig=undefined FUN_0040d920() cc=unknown
// callers: FUN_0040dbc4,FUN_00466508
// callees: 

undefined4 FUN_0040d920(int param_1,undefined *param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *local_8;
  
  if ((param_1 != 0) && (param_2 != (undefined *)0x0)) {
    iVar2 = 0;
    local_8 = (ushort *)(param_1 + 0x890);
    do {
      uVar1 = *local_8;
      for (iVar3 = 0; (uVar1 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
        if (((uVar1 & 1) != 0) && (&DAT_005a43d0 + (iVar2 * 0x10 + iVar3) * 0xadc == param_2)) {
          return 1;
        }
        uVar1 = (short)uVar1 >> 1;
      }
      iVar2 = iVar2 + 1;
      local_8 = local_8 + 1;
    } while (iVar2 < 7);
  }
  return 0;
}

