// FUN_0048ba70 @ 0048ba70 size=54 sig=undefined FUN_0048ba70() cc=unknown
// callers: FUN_0048baa6
// callees: GlobalMemoryStatus

SIZE_T FUN_0048ba70(int param_1)

{
  _MEMORYSTATUS local_24;
  
  if (param_1 == 1) {
    local_24.dwAvailVirtual = 0;
  }
  else {
    local_24.dwLength = 0x20;
    GlobalMemoryStatus(&local_24);
    if (param_1 == 0) {
      local_24.dwAvailVirtual = local_24.dwAvailPhys;
    }
  }
  return local_24.dwAvailVirtual;
}

