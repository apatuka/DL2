// FUN_00431128 @ 00431128 size=304 sig=undefined FUN_00431128() cc=unknown
// callers: CheckSubUnit,CheckSubTech,CheckSubInfo
// callees: FUN_00430c38,FUN_0044a000,FUN_0048de8e,free,FUN_004152ec,FUN_00431088,FUN_0048df30,FUN_00412f10,FUN_0048db5d,FUN_0048e169,FUN_00430cd8,FUN_00432cf4,FUN_004503f4,FUN_004152e0,FUN_00412e94,UpdateWindow

void FUN_00431128(void)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  iVar3 = FUN_004503f4(7,3,0xffffffff);
  if (iVar3 == 0) {
    FUN_00430c38();
  }
  else {
    FUN_004152e0();
    UpdateWindow(DAT_004d5974);
    iVar3 = FUN_00430cd8(iVar3);
    if (iVar3 != 0) {
      FUN_00432cf4();
      FUN_0044a000();
      DAT_004d59a4 = 1;
      FUN_0048db5d(0);
      DAT_004d59a4 = 0;
      FUN_00431088();
      if (DAT_004c42ec == 0) {
        while (uVar1 = DAT_004d59a4, *(char *)(DAT_004c42e4 + 0x3c) != '\0') {
          DAT_004d59a4 = 1;
          FUN_0048db5d(0);
          DAT_004d59a4 = uVar1;
          iVar3 = FUN_0048e169(1,local_10,local_c,local_8);
          if (iVar3 != 0) {
            FUN_00412e94(DAT_004c42e4);
          }
          cVar2 = FUN_0048de8e();
          if (cVar2 != '\0') {
            FUN_0048df30();
            FUN_00412e94(DAT_004c42e4);
          }
        }
        DAT_004c5b78 = 0;
        DAT_004c5b70 = 0;
        DAT_004c5b7c = 0;
        DAT_004c5b74 = 0;
        FUN_00412f10(DAT_004c42e4);
      }
      DAT_004c42f0 = 1;
      if (DAT_004c42e8 != 0) {
        free(DAT_004c42e8);
        DAT_004c42e8 = 0;
      }
    }
  }
  FUN_004152ec();
  return;
}

