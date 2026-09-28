// FUN_00495241 @ 00495241 size=175 sig=undefined FUN_00495241() cc=unknown
// callers: 
// callees: GetSystemTime,FUN_00488d30,FUN_00495162,FUN_00488a67,FUN_0049512a
// strings: \"err.bak\"|\"err.log\"|\"Error log started, %d/%d/%d, %d:%d:%d\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00495241(void)

{
  undefined1 local_21c [260];
  undefined1 local_118 [260];
  _SYSTEMTIME local_14;
  
  if ((_DAT_0051dcc4 & 0x80000000) != 0) {
    _DAT_0051dcc4 = _DAT_0051dcc4 & 0x7fffffff;
    FUN_0049512a(local_118,s_err_bak_0051e039);
    FUN_0049512a(local_21c,s_err_log_0051e041);
    FUN_00488a67(local_118);
    FUN_00488d30(local_21c,local_118);
    FUN_00488a67(local_21c);
    _DAT_0051dcc4 = _DAT_0051dcc4 | 0x80000000;
    GetSystemTime(&local_14);
    FUN_00495162(s_Error_log_started___d__d__d___d__0051e049,local_14.wMonth,local_14.wDay,
                 local_14.wYear,local_14.wHour,local_14.wMinute,local_14.wSecond);
  }
  return;
}

