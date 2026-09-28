// FUN_004a94a8 @ 004a94a8 size=31 sig=undefined FUN_004a94a8() cc=unknown
// callers: 
// callees: free

void FUN_004a94a8(undefined4 *param_1,byte param_2)

{
  if ((param_1 != (undefined4 *)0x0) && (*param_1 = &PTR_FUN_0051fcdc, (param_2 & 1) != 0)) {
    free(param_1);
  }
  return;
}

