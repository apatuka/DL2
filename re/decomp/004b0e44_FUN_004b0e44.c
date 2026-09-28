// FUN_004b0e44 @ 004b0e44 size=24 sig=undefined FUN_004b0e44() cc=unknown
// callers: FUN_004b0654
// callees: GlobalMemoryStatus

SIZE_T FUN_004b0e44(void)

{
  _MEMORYSTATUS local_20;
  
  local_20.dwLength = 0x20;
  GlobalMemoryStatus(&local_20);
  return local_20.dwAvailPhys;
}

