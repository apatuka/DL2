// FUN_0042a2c4 @ 0042a2c4 size=84 sig=undefined FUN_0042a2c4() cc=unknown
// callers: FUN_00428b74,FUN_0042ac68,FUN_00449084,FUN_0042b280
// callees: FUN_0048c434,FUN_0042a08c,FUN_0049a93f,FUN_0049a8ed,FUN_0049aa64,FUN_00414f38,FUN_0049f22b

void FUN_0042a2c4(void)

{
  undefined4 uVar1;
  undefined1 auStack_14 [16];
  
  FUN_00414f38(DAT_004b9bf0);
  uVar1 = DAT_0051bddc;
  if (DAT_004b9bf0 != 0) {
    FUN_0048c434(*(undefined4 *)(DAT_004b9bf0 + 0x3c));
    FUN_0049a8ed();
    FUN_0049f22b(DAT_004b9bf0,auStack_14);
    FUN_0049aa64(auStack_14);
    FUN_0042a08c();
    FUN_0049a93f();
    FUN_0048c434(uVar1);
  }
  return;
}

