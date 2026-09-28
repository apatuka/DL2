// FUN_00415274 @ 00415274 size=75 sig=undefined FUN_00415274() cc=unknown
// callers: FUN_0046f5d4,FUN_00472ed0,XenoIntro,InitCYGame,FUN_00468a28,XenoBackground
// callees: FUN_0049415f,FUN_00490ab3,FUN_00494f62

void FUN_00415274(void)

{
  if ((DAT_004b706c == 0) &&
     (DAT_004b706c = FUN_00490ab3(0,0x47414d49,0x52535243,0,0x80000000), DAT_004b706c == 0)) {
    return;
  }
  FUN_0049415f(DAT_004b706c);
  FUN_00494f62(DAT_004d5c28,1);
  return;
}

