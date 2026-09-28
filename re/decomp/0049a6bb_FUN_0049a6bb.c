// FUN_0049a6bb @ 0049a6bb size=114 sig=undefined FUN_0049a6bb() cc=unknown
// callers: FUN_0049a760
// callees: FUN_00499c5d,FUN_00499dfc,FUN_0049a317,FUN_00499d88,FUN_00499e70,FUN_00499f04,FUN_00498ba9

void FUN_0049a6bb(void)

{
  FUN_0049a317();
  FUN_00499c5d();
  FUN_00499d88(0x32,6);
  FUN_00499dfc(0x32,0xc);
  FUN_00499e70(10,6);
  FUN_00499f04(0x1e,0xc);
  if (DAT_0051e350 == 0) {
    DAT_0051e350 = FUN_00498ba9(0x4000);
  }
  if (DAT_0051e354 == 0) {
    DAT_0051e354 = FUN_00498ba9(0x140);
    DAT_0051e358 = DAT_0051e354 + 0x140;
  }
  return;
}

