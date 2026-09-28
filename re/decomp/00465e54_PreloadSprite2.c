// PreloadSprite2 @ 00465e54 size=37 sig=undefined PreloadSprite2() cc=unknown
// callers: WinMain,FUN_004618e8
// callees: FUN_00483524,DebugMessage,LoadGlobalSprites,FUN_00465e20
// strings: \"Could not load global sprites.\"

/* Loads the global sprite set (calls LoadGlobalSprites) */

void PreloadSprite2(void)

{
  int iVar1;
  
  FUN_00483524();
  iVar1 = LoadGlobalSprites(&DAT_004d4dd0,0x11);
  if (iVar1 == 0) {
    DebugMessage(s_Could_not_load_global_sprites__004d4efa);
  }
  FUN_00465e20();
  return;
}

