// LoadSmacker @ 00487b80 size=89 sig=undefined LoadSmacker() cc=unknown
// callers: WinMain,FUN_0046cc6c
// callees: FUN_004589b0,LoadLibraryA
// strings: \"SMACKW32.DLL\"

/* Loads SMACKW32.DLL */

void LoadSmacker(void)

{
  FUN_004589b0();
  if (DAT_00583b98 == 0) {
    DAT_0065e54c = LoadLibraryA(s_SMACKW32_DLL_00512700);
  }
  else if (DAT_00583b98 == 1) {
    DAT_0065e54c = LoadLibraryA(s_SMACKW32_DLL_00512700);
  }
  else if (DAT_00583b98 == 2) {
    DAT_0065e54c = LoadLibraryA(s_SMACKW32_DLL_00512700);
  }
  return;
}

