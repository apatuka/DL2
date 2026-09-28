// FUN_00494b6b @ 00494b6b size=170 sig=undefined FUN_00494b6b() cc=unknown
// callers: FUN_00494b06,FUN_00494449
// callees: EnterCriticalSection,FUN_0048c85e,LeaveCriticalSection

void FUN_00494b6b(void)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_0065ecac == &DAT_0065e644) && (DAT_0051b83c != 0)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  if (((DAT_0065ecb8 != 0) && (DAT_0051dc8c != 0)) && (DAT_0065ecac != (undefined *)0x0)) {
    local_14 = 0;
    local_10 = 0;
    local_c = *(undefined4 *)(DAT_0065ecb8 + 4);
    local_8 = *(undefined4 *)(DAT_0065ecb8 + 8);
    FUN_0048c85e(DAT_0065ecb8,DAT_0065ecac,&local_14,&DAT_0065ec9c,0,0,0);
    DAT_0051dc8c = 0;
  }
  if ((DAT_0065ecac == &DAT_0065e644) && (DAT_0051b83c != 0)) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return;
}

