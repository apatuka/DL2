// FUN_00468da0 @ 00468da0 size=257 sig=undefined FUN_00468da0() cc=unknown
// callers: FUN_0043a1f8,FUN_00468d3c
// callees: FUN_004a6b48,FUN_00461e9c,FUN_0042836c,memset,sprintf
// strings: \"%s is not a valid saved game.  Unable to load game.\"|\"Load Game Error\"

undefined4 FUN_00468da0(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 local_404 [1024];
  
  memset(&DAT_004d5b10,0xff,0x14);
  if (param_1 == 0) {
    DAT_004d59a8 = 0;
    uVar1 = 0x35;
  }
  else {
    FUN_004a6b48(&DAT_0058ed2e,param_1,0x3ff);
    DAT_0058f12e = 0;
    DAT_004d5aec = FUN_00461e9c(&DAT_0058ed2e,&DAT_0058f12e);
    iVar3 = 0;
    puVar2 = &DAT_0059f162;
    do {
      *puVar2 = 0xff;
      puVar2[-1] = 0;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 0x2d8;
    } while (iVar3 < 7);
    (&DAT_0059f161)[DAT_0058f1f4 * 0x2d8] = 1;
    DAT_004d513c = 1;
    if (DAT_004d5aec < 1) {
      sprintf(local_404,PTR_s__s_is_not_a_valid_saved_game__Un_00509a0c,&DAT_0058ed2e);
      FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_404,4,0,1);
      DAT_0058ed2e = 0;
      DAT_004d59a8 = 0;
      uVar1 = 0x35;
    }
    else {
      uVar1 = 0x38;
    }
  }
  return uVar1;
}

