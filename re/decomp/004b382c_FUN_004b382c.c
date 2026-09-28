// FUN_004b382c @ 004b382c size=100 sig=undefined FUN_004b382c() cc=unknown
// callers: FUN_004ac974,FUN_004ab648,FUN_004acb90
// callees: FUN_004b38b0,InitializeCriticalSection,LeaveCriticalSection,EnterCriticalSection

void FUN_004b382c(undefined4 *param_1,undefined4 param_2)

{
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0069f894);
  if (0x1ff < DAT_006a2894) {
    FUN_004b38b0(param_2);
  }
  InitializeCriticalSection((LPCRITICAL_SECTION)(&DAT_0069f894 + DAT_006a2894 * 0x18));
  *param_1 = &DAT_0069f894 + DAT_006a2894 * 0x18;
  DAT_006a2894 = DAT_006a2894 + 1;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0069f894);
  return;
}

