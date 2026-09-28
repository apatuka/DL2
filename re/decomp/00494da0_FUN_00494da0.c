// FUN_00494da0 @ 00494da0 size=79 sig=undefined FUN_00494da0() cc=unknown
// callers: FUN_00494f0f,FUN_00494def
// callees: ResumeThread,EnterCriticalSection,LeaveCriticalSection

void FUN_00494da0(void)

{
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  if ((DAT_0051dc98 != (HANDLE)0x0) && (DAT_0051dc88 != 0)) {
    DAT_0051dc88 = 0;
    ResumeThread(DAT_0051dc98);
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return;
}

