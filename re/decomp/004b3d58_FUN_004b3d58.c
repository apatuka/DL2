// FUN_004b3d58 @ 004b3d58 size=42 sig=undefined FUN_004b3d58() cc=unknown
// callers: FUN_004b1678
// callees: GetLocalTime

void FUN_004b3d58(uint *param_1)

{
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  *(undefined1 *)(param_1 + 1) = (undefined1)local_14.wDay;
  *(undefined1 *)((int)param_1 + 5) = (undefined1)local_14.wMonth;
  *param_1 = (uint)local_14.wYear;
  return;
}

