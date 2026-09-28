// FUN_0045e99c @ 0045e99c size=165 sig=undefined FUN_0045e99c() cc=unknown
// callers: FUN_0047361c
// callees: FUN_0045e274,FUN_0045dfd4,FUN_00449d54

undefined4 FUN_0045e99c(void)

{
  int iVar1;
  
  if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
    if (DAT_004c5b50 == 1) {
      iVar1 = (int)DAT_004d5b18;
    }
    else {
      iVar1 = DAT_004c5b50 + -1;
    }
    while (DAT_004c5b50 != iVar1) {
      if ((char)(&DAT_005a43f0)[iVar1 * 0xadc] == DAT_0058f1f4) {
        if (DAT_004d59b4 == 0) {
          FUN_0045e274((int)*(char *)(&DAT_005a4450)[iVar1 * 0x2b7],
                       (int)((char *)(&DAT_005a4450)[iVar1 * 0x2b7])[1]);
          return 0;
        }
        FUN_0045dfd4(iVar1,1);
        FUN_00449d54(iVar1);
        return 0;
      }
      if (iVar1 < 2) {
        iVar1 = (int)DAT_004d5b18;
      }
      else {
        iVar1 = iVar1 + -1;
      }
    }
  }
  return 0;
}

