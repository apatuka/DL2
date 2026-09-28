// FUN_00498994 @ 00498994 size=29 sig=undefined FUN_00498994() cc=unknown
// callers: FUN_00498dba,FUN_00498db0
// callees: GlobalMemoryStatus

SIZE_T FUN_00498994(void)

{
  _MEMORYSTATUS local_24;
  
  local_24.dwLength = 0x20;
  GlobalMemoryStatus(&local_24);
  return local_24.dwAvailVirtual;
}

