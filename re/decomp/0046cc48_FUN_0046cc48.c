// FUN_0046cc48 @ 0046cc48 size=34 sig=undefined FUN_0046cc48() cc=unknown
// callers: ShutdownGame
// callees: FreeLibrary

void FUN_0046cc48(void)

{
  if (DAT_006520a0 != (HMODULE)0x0) {
    FreeLibrary(DAT_006520a0);
    DAT_006520a0 = (HMODULE)0x0;
    PTR_FUN_004d5c14 = FUN_0046cc00;
  }
  return;
}

