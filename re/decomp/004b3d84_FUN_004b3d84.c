// FUN_004b3d84 @ 004b3d84 size=56 sig=undefined FUN_004b3d84() cc=unknown
// callers: FUN_004b1678
// callees: GetLocalTime

void FUN_004b3d84(undefined1 *param_1)

{
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  param_1[1] = (undefined1)local_14.wHour;
  *param_1 = (undefined1)local_14.wMinute;
  param_1[3] = (undefined1)local_14.wSecond;
  param_1[2] = (char)((ulonglong)local_14.wMilliseconds / 10);
  return;
}

