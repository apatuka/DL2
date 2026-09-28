// FUN_00425268 @ 00425268 size=251 sig=undefined FUN_00425268() cc=unknown
// callers: FUN_00425364
// callees: FUN_00412f10,FUN_00412d38,FUN_004a322d,Sleep,FUN_004251d8,FUN_0048df30,FUN_0048e169,FUN_0048db5d,FUN_0048de8e

undefined4 FUN_00425268(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  if ((((DAT_00557548 == 0) && (DAT_00557530 != 0)) && (DAT_0055754c == 0)) &&
     (*(char *)(DAT_00557530 + 0x3c) == '\0')) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    Sleep(1000);
    FUN_00412f10(DAT_00557530);
    FUN_00412d38(DAT_00557530,*(undefined4 *)(DAT_004b7c80 + 0x3c));
    FUN_004251d8();
    uVar2 = 1;
  }
  else {
    DAT_004d59a4 = 1;
    DAT_0051b824 = 1;
    FUN_0048db5d(0);
    FUN_004a322d(DAT_004b7c80);
    iVar3 = FUN_0048e169(1,local_c,local_8,local_4);
    if (iVar3 == 0) {
      cVar1 = FUN_0048de8e();
      if (cVar1 == '\0') {
        uVar2 = 0;
        DAT_004d59a4 = 0;
      }
      else {
        FUN_004251d8();
        DAT_004d59a4 = 0;
        uVar2 = FUN_0048df30();
      }
    }
    else {
      FUN_004251d8();
      uVar2 = 1;
      DAT_004d59a4 = 0;
    }
  }
  return uVar2;
}

