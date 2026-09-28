// FUN_00489c3e @ 00489c3e size=62 sig=undefined FUN_00489c3e() cc=unknown
// callers: InitCYGame,FUN_00482a8c
// callees: _SmackSoundUseDirectSound@4,FUN_00495b28

undefined4 FUN_00489c3e(void)

{
  if (DAT_0051b5f4 == 0) {
    FUN_00495b28(3,FUN_00489ae1,FUN_00489c7c,&DAT_0051b5f8);
    _SmackSoundUseDirectSound_4(DAT_0051b5fc);
    DAT_0051b5f4 = 1;
  }
  return 1;
}

