// FUN_0046cc14 @ 0046cc14 size=50 sig=undefined FUN_0046cc14() cc=unknown
// callers: WinMain
// callees: GetProcAddress,LoadLibraryA
// strings: \"BWCC32.DLL\"|\"BWCCRegister\"

void FUN_0046cc14(void)

{
  FARPROC pFVar1;
  
  DAT_006520a0 = LoadLibraryA(s_BWCC32_DLL_004d5c39);
  if (DAT_006520a0 != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(DAT_006520a0,s_BWCCRegister_004d5c44);
    if (pFVar1 != (FARPROC)0x0) {
      PTR_FUN_004d5c14 = pFVar1;
    }
  }
  return;
}

