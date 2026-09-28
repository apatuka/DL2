// FUN_00498dba @ 00498dba size=67 sig=undefined FUN_00498dba() cc=unknown
// callers: 
// callees: FUN_00498994,GlobalMemoryStatus

void FUN_00498dba(SIZE_T *param_1)

{
  SIZE_T SVar1;
  _MEMORYSTATUS local_24;
  
  local_24.dwLength = 0x20;
  GlobalMemoryStatus(&local_24);
  SVar1 = FUN_00498994();
  param_1[1] = SVar1;
  param_1[2] = param_1[1];
  *param_1 = local_24.dwTotalVirtual;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}

