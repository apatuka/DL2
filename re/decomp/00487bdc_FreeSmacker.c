// FreeSmacker @ 00487bdc size=16 sig=undefined FreeSmacker() cc=unknown
// callers: ShutdownGame,WinMain
// callees: FreeLibrary

/* Unloads SMACKW32.DLL */

void FreeSmacker(void)

{
  if (DAT_0065e54c != (HMODULE)0x0) {
    FreeLibrary(DAT_0065e54c);
  }
  return;
}

