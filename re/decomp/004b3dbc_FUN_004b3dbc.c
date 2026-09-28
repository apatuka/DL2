// FUN_004b3dbc @ 004b3dbc size=75 sig=undefined FUN_004b3dbc() cc=unknown
// callers: WinMain
// callees: GetLocalTime,FUN_004b3a1c

void FUN_004b3dbc(undefined4 *param_1)

{
  undefined4 uVar1;
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  uVar1 = FUN_004b3a1c(local_14.wYear - 0x76c,local_14.wMonth - 1,local_14.wDay - 1,local_14.wHour,
                       local_14.wMinute,local_14.wSecond);
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = uVar1;
  }
  return;
}

