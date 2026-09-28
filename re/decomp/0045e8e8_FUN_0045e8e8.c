// FUN_0045e8e8 @ 0045e8e8 size=180 sig=undefined FUN_0045e8e8() cc=unknown
// callers: FUN_0047361c
// callees: FUN_0045e274,FUN_0045dfd4,FUN_00449d54

undefined4 FUN_0045e8e8(void)

{
  int iVar1;
  
  if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
    if (DAT_004d5b18 < DAT_004c5b50) {
      iVar1 = 1;
    }
    else {
      iVar1 = DAT_004c5b50 + 1;
    }
    while (DAT_004c5b50 != iVar1) {
      if ((char)(&DAT_005a43f0)[iVar1 * 0xadc] == DAT_0058f1f4) {
        if (DAT_004d59b4 == 0) {
          FUN_0045e274((int)*(char *)(&DAT_005a4450)[iVar1 * 0x2b7],
                       (int)((char *)(&DAT_005a4450)[iVar1 * 0x2b7])[1]);
          return 0;
        }
        if (DAT_004d59b4 != 1) {
          return 0;
        }
        FUN_0045dfd4(iVar1,1);
        FUN_00449d54(iVar1);
        return 0;
      }
      iVar1 = iVar1 + 1;
      if (DAT_004d5b18 < iVar1) {
        iVar1 = 1;
      }
    }
  }
  return 0;
}

