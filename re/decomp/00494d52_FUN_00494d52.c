// FUN_00494d52 @ 00494d52 size=78 sig=undefined FUN_00494d52() cc=unknown
// callers: FUN_00494def
// callees: EnterCriticalSection,LeaveCriticalSection,SuspendThread

void FUN_00494d52(void)

{
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  if ((DAT_0051dc98 != (HANDLE)0x0) && (DAT_0051dc88 == 0)) {
    DAT_0051dc88 = 1;
    SuspendThread(DAT_0051dc98);
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return;
}

