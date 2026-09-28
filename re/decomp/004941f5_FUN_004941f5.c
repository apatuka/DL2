// FUN_004941f5 @ 004941f5 size=185 sig=undefined FUN_004941f5() cc=unknown
// callers: FUN_004152e0,FUN_004152ec
// callees: FUN_00494b06,EnterCriticalSection,FUN_00496cc3,LeaveCriticalSection,FUN_004940f0,FUN_0049497a

undefined4 FUN_004941f5(undefined4 param_1)

{
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  FUN_00494b06();
  FUN_004940f0(param_1);
  DAT_0051dc70 = 0;
  if (DAT_0065ec80 != 0) {
    FUN_00496cc3(DAT_0065ecb0,DAT_0051dc78,0,0,&DAT_0065ec8c);
    DAT_0065ec90 = DAT_0065ec90 + DAT_0065ec88;
    DAT_0065ec98 = DAT_0065ec98 + DAT_0065ec88;
    DAT_0065ec8c = DAT_0065ec8c + DAT_0065ec84;
    DAT_0065ec94 = DAT_0065ec94 + DAT_0065ec84;
  }
  if (DAT_0051dc98 == 0) {
    FUN_00494b06();
  }
  else {
    FUN_0049497a(0,1);
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return param_1;
}

