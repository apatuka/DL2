// FUN_00494def @ 00494def size=115 sig=undefined FUN_00494def() cc=unknown
// callers: FUN_00487a00,FUN_0046f5d4,XenoIntro,FUN_00472ed0,FUN_0046ce10,InitCYGame,FUN_00468a28,WinMain,FUN_0043611c
// callees: FUN_00494b06,EnterCriticalSection,FUN_00494da0,FUN_00494d52,LeaveCriticalSection,FUN_0049497a

int FUN_00494def(int param_1)

{
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  if (param_1 == 0) {
    if (DAT_0065ec7c == 1) {
      FUN_00494b06();
    }
    DAT_0065ec7c = DAT_0065ec7c + -1;
    if (DAT_0065ec7c == 0) {
      FUN_00494d52();
    }
  }
  else {
    DAT_0065ec7c = DAT_0065ec7c + 1;
    if (DAT_0065ec7c == 1) {
      FUN_0049497a(0,0);
      FUN_00494da0();
    }
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return DAT_0065ec7c;
}

