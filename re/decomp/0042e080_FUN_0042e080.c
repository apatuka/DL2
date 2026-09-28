// FUN_0042e080 @ 0042e080 size=409 sig=undefined FUN_0042e080() cc=unknown
// callers: FUN_0042e2f8,FUN_0042e2b8
// callees: FUN_0042deec,FUN_0042dee0,FUN_0042d574,UpdateWindow,FUN_0042dbb8,FUN_00475344,FUN_0042d4e4,FUN_00426594,FUN_0048db5d,FUN_004a2cb5,FUN_0042d550,FUN_0042e66c,FUN_00477620

longlong FUN_0042e080(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004d5aa0 == '\0') {
    FUN_0042dbb8();
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042dee0();
  iVar1 = FUN_004a2cb5(DAT_004c3668,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c3668 + 100) == 0)) {
    switch(local_4) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      iVar1 = FUN_0042d4e4(local_4);
      if (iVar1 != DAT_004c366c) {
        DAT_004c366c = iVar1;
        FUN_0042d550();
        FUN_0042e66c(DAT_004c366c);
        FUN_0042deec();
      }
      break;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
      if (DAT_004d5aa0 == '\0') {
        (&DAT_005a0548)[DAT_0058f1f4] = (char)local_4 + -9;
        FUN_0042d574();
      }
      else {
        DAT_004c3670 = local_4 - 9;
        FUN_0042d574();
      }
      break;
    case 0xe:
      FUN_00426594(&DAT_004d480c + DAT_004c366c * 0x24);
      break;
    case 0xf:
      if (DAT_004d5aa0 != '\0') {
        DAT_004d59a4 = 0;
        return CONCAT44(local_4,local_4);
      }
      if (DAT_00557c7c == DAT_0058f1f4) {
        DAT_004c3664 = DAT_004c366c;
        FUN_00477620(DAT_00557c7c,DAT_004c366c);
        FUN_0042deec();
        FUN_0042dee0();
        UpdateWindow(DAT_004d5978);
      }
      break;
    case 0x10:
      if (DAT_004d5aa0 != '\0') {
        DAT_004d59a4 = 0;
        return CONCAT44(local_4,local_4);
      }
      DAT_0058f1ec = 1;
      DAT_00557c80 = 1;
      if (DAT_0058f1fc != 0) {
        FUN_00475344();
      }
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

