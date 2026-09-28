// FUN_0045ac80 @ 0045ac80 size=277 sig=undefined FUN_0045ac80() cc=unknown
// callers: FUN_0045ad98,FUN_0045bc10,FUN_0046e730
// callees: FUN_0045e274,FUN_0043a768,FUN_0049eb44,FUN_00459068,FUN_0044a000,FUN_0043a854

void FUN_0045ac80(void)

{
  if ((DAT_004d59b4 == 1) || (DAT_004d59b4 == 0)) {
    DAT_004c5b68 = 1;
    FUN_00459068();
    if (DAT_004d59b4 == 1) {
      DAT_004d59b4 = 0;
      if (DAT_004d5aa0 == '\0') {
        FUN_0049eb44(DAT_004c48a0,0xd,1,0xb,0,0);
      }
      else {
        FUN_0049eb44(DAT_004c48a0,0xd,1,0xb,0,0);
      }
      FUN_0043a854();
      FUN_0045e274((int)*(char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7],
                   (int)((char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7])[1]);
    }
    else if (DAT_004d59b4 == 0) {
      DAT_004d59b4 = 1;
      if (DAT_004d5aa0 == '\0') {
        FUN_0049eb44(DAT_004c48a0,0xd,1,0xb,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c48a0,0xd,1,0xb,1,0);
      }
      FUN_0043a768();
    }
    FUN_0044a000();
    DAT_004c5b68 = 0;
  }
  return;
}

