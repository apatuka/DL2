// FUN_0043df3c @ 0043df3c size=82 sig=undefined FUN_0043df3c() cc=unknown
// callers: FUN_0043e138,CheckViewCombat,FUN_0043e590
// callees: 

int FUN_0043df3c(int param_1)

{
  short *psVar1;
  
  param_1 = param_1 + -1;
  psVar1 = &DAT_0057bd40 + param_1 * 0x43;
  while( true ) {
    if (param_1 < 0) {
      return -1;
    }
    if (*psVar1 == DAT_0058f1f4) {
      return param_1;
    }
    if (DAT_0058f1f4 == psVar1[1]) {
      return param_1;
    }
    if (DAT_00583c20 != 0) break;
    param_1 = param_1 + -1;
    psVar1 = psVar1 + -0x43;
  }
  return param_1;
}

