// FUN_0046f5d4 @ 0046f5d4 size=505 sig=undefined FUN_0046f5d4() cc=unknown
// callers: FUN_004618e8,WinMain
// callees: FUN_00415274,FUN_0046eea0,FUN_004360ec,FUN_0042836c,FUN_004811c8,FUN_0045e274,DestroyWindow,FUN_0043c260,FUN_004a4113,FUN_00494def,XenoBackground
// strings: \"There is not enough memory to run the game.\\n\\nTry playing Deadlock 2 on a smaller map.\"|\"Out of Memory Error\"

void FUN_0046f5d4(void)

{
  int iVar1;
  
  if (DAT_004d5978 != (HWND)0x0) {
    if (DAT_004d59b4 == 0x2a) {
      FUN_004360ec();
    }
    FUN_00415274(0);
    FUN_004a4113();
    FUN_00494def(0);
    DestroyWindow(DAT_004d5978);
    DAT_004d5978 = (HWND)0x0;
    DAT_004d59b4 = 0x32;
    FUN_00494def(1);
  }
  iVar1 = FUN_004811c8();
  if (iVar1 == 0) {
    FUN_0042836c(PTR_s_Out_of_Memory_Error_00509854,PTR_s_There_is_not_enough_memory_to_ru_00509858,
                 4,0,0);
    DAT_0058f1ec = 1;
    return;
  }
  FUN_00494def(0);
  XenoBackground();
  FUN_00494def(1);
  FUN_0043c260();
  if (DAT_004d5974 == 0) {
    FUN_0042836c(PTR_s_Out_of_Memory_Error_00509854,PTR_s_There_is_not_enough_memory_to_ru_00509858,
                 4,0,0);
    DAT_0058f1ec = 1;
    return;
  }
  FUN_0046eea0();
  if ((DAT_004d5aa0 == '\0') || ((-1 < DAT_0058f1f4 && (DAT_0058f1f4 < DAT_004d5aec)))) {
    DAT_004c5b50 = (int)(short)(&DAT_0059f166)[DAT_0058f1f4 * 0x16c];
  }
  else {
    DAT_004c5b50 = 0;
  }
  if ((DAT_004c5b50 == 0) || (DAT_004c5b50 == -1)) {
    for (iVar1 = 1; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
      if ((&DAT_005a444e)[iVar1 * 0xadc] != '\0') {
        if ((DAT_004c5b50 == 0) || (DAT_004c5b50 == -1)) {
          DAT_004c5b50 = iVar1;
        }
        if ((char)(&DAT_005a43f0)[iVar1 * 0xadc] == DAT_0058f1f4) {
          FUN_0045e274((int)*(char *)(&DAT_005a4450)[iVar1 * 0x2b7],
                       (int)((char *)(&DAT_005a4450)[iVar1 * 0x2b7])[1]);
          (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] | 1;
          break;
        }
      }
    }
  }
  else {
    FUN_0045e274((int)*(char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7],
                 (int)((char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7])[1]);
    (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] | 3;
  }
  DAT_00657de0 = &DAT_005a43d0 + DAT_004c5b50 * 0xadc;
  return;
}

