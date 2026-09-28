// FUN_0048af1c @ 0048af1c size=39 sig=undefined FUN_0048af1c() cc=unknown
// callers: FUN_00494ebf
// callees: InitializeCriticalSection

undefined4 FUN_0048af1c(void)

{
  if (DAT_0051b83c == 0) {
    InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  DAT_0051b83c = 1;
  return 1;
}

