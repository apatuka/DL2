// FUN_0049a760 @ 0049a760 size=136 sig=undefined FUN_0049a760() cc=unknown
// callers: InitCYGame,FUN_00492d67,FUN_0047fffc,FUN_0049d7f4,FUN_00458d80,FUN_00459864,FUN_0049fe03,FUN_00493564,FUN_0049fd2e,FUN_00496e80,FUN_0049f9c0,BlitSprite8
// callees: FUN_0049a6bb,FUN_0049a72d,FUN_00498ba9

int FUN_0049a760(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0051e35c;
  if (DAT_0051e35c == 0) {
    FUN_0049a6bb();
    DAT_0051e21c = FUN_00498ba9(0x408);
    iVar2 = 0x80008;
  }
  if (param_1 == 0) {
    param_1 = DAT_0065e590;
  }
  if ((param_1 & 0xffff0000) == 0) {
    param_1 = param_1 | param_1 << 0x10;
  }
  iVar1 = FUN_0049a72d(param_1);
  DAT_0069ee90 = &PTR_LAB_0051e230 + iVar1 * 8;
  DAT_0069ee94 = &PTR_FUN_0051e290 + iVar1 * 8;
  DAT_0069ee98 = &PTR_LAB_0051e2f0 + iVar1 * 8;
  DAT_0051e35c = param_1;
  return iVar2;
}

