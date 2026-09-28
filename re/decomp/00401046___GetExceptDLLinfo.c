// __GetExceptDLLinfo @ 00401046 size=5 sig=undefined __GetExceptDLLinfo() cc=unknown
// callers: 
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __GetExceptDLLinfo(undefined4 *param_1)

{
                    /* 0x1046  2  __GetExceptDLLinfo */
  _DAT_0051f044 = FUN_004010f9();
  _DAT_0051f044 = _DAT_0051f044 + 0x30;
  _DAT_0051f028 = &DAT_0051f114;
  _DAT_0051f02c = &__DebuggerHookData;
  *param_1 = 0x82727349;
  param_1[1] = &DAT_0051f01c;
  return;
}

