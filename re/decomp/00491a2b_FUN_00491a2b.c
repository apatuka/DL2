// FUN_00491a2b @ 00491a2b size=163 sig=undefined FUN_00491a2b() cc=unknown
// callers: FUN_0049d7f4,FUN_004a016e,FUN_0048468c,FUN_004a08c5,FUN_00492d67,FUN_0049d58b,FUN_004844e0,FUN_0049e47a,FUN_0048463c,FUN_004a060f,FUN_0049ff48,FUN_004897ea,FUN_00419154,FUN_004a03cf,FUN_004193e0,FUN_0049ebfb,FUN_0049e3d7
// callees: FUN_00491bf7,FUN_0048e656
// strings: \"..\\\\src\\\\font.c\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00491a2b(int param_1)

{
  DAT_0065ec48 = (undefined4 *)((int)DAT_0065ec48 - 0x28);
  if (DAT_0065ec48 < DAT_0051dc0c) {
    FUN_0048e656(0xfa,s____src_font_c_0051dc28);
  }
  *DAT_0065ec48 = DAT_0051dc10;
  DAT_0065ec48[1] = DAT_0065ec10;
  DAT_0065ec48[2] = DAT_0065ec14;
  DAT_0065ec48[3] = DAT_0065ec18;
  DAT_0065ec48[4] = DAT_0065ec1c;
  DAT_0065ec48[5] = DAT_0065ec50;
  DAT_0065ec48[6] = _DAT_0051dc14;
  DAT_0065ec48[8] = DAT_0065ec58;
  DAT_0065ec48[9] = DAT_0065ec5c;
  DAT_0065ec48[7] = DAT_0065ec54;
  if (param_1 != 0) {
    FUN_00491bf7(param_1);
  }
  return;
}

