// FUN_004b17e8 @ 004b17e8 size=113 sig=undefined FUN_004b17e8() cc=unknown
// callers: FUN_004b185c,FUN_004b1874
// callees: FUN_004ac940,FUN_004b2968,FUN_004b28e0,FUN_004ab6ec,FUN_004b281c,FUN_004b17e4,FUN_004b2958

void FUN_004b17e8(int param_1,int param_2,undefined4 param_3)

{
  FUN_004b2958();
  if (param_1 == 0) {
    while (DAT_005212e8 != 0) {
      DAT_005212e8 = DAT_005212e8 + -1;
      (**(code **)(&DAT_0069f7a0 + DAT_005212e8 * 4))();
    }
    FUN_004b28e0();
    (*(code *)PTR_FUN_005212ec)();
  }
  if (param_2 == 0) {
    if (param_1 == 0) {
      (*(code *)PTR_FUN_005212f0)();
      (*(code *)PTR_FUN_005212f4)();
    }
    FUN_004b2968();
    FUN_004ac940();
    FUN_004ab6ec();
    FUN_004b281c(param_3);
  }
  FUN_004b2968();
  return;
}

