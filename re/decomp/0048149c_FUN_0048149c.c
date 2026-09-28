// FUN_0048149c @ 0048149c size=163 sig=undefined FUN_0048149c() cc=unknown
// callers: FUN_00449870
// callees: FUN_00445270,FUN_00444e88,BirthCombatSprites,FUN_004152ec,FUN_0048d32c,FUN_004152e0,FUN_00465df8,FUN_0048d2e7,FUN_004810cc,FUN_0048125c

void FUN_0048149c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  DAT_00657de0 = param_3;
  FUN_004152e0();
  FUN_00465df8(3);
  DAT_004dcc14 = 0xffffffff;
  FUN_0048125c(param_1,param_2,600,400);
  DAT_004c5460 = 600;
  DAT_004c5464 = 400;
  DAT_004c5458 = 0x16;
  DAT_004c545c = 0x18;
  DAT_004dcc24 = 0;
  DAT_004dcc28 = 0;
  FUN_0048d2e7(DAT_004dcc1c);
  FUN_004810cc(param_3);
  FUN_004152ec();
  FUN_00444e88();
  BirthCombatSprites();
  FUN_00445270(1);
  FUN_0048d32c();
  return;
}

