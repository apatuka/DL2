// FUN_00488e62 @ 00488e62 size=59 sig=undefined FUN_00488e62() cc=unknown
// callers: FUN_0049512a
// callees: FUN_0048937d,GetModuleFileNameA

void FUN_00488e62(undefined1 *param_1)

{
  DWORD DVar1;
  CHAR local_108 [260];
  
  *param_1 = 0;
  DVar1 = GetModuleFileNameA((HMODULE)0x0,local_108,0x104);
  if (DVar1 != 0) {
    FUN_0048937d(local_108,param_1);
  }
  return;
}

