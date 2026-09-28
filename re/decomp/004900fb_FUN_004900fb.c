// FUN_004900fb @ 004900fb size=39 sig=undefined FUN_004900fb() cc=unknown
// callers: FUN_004901c6
// callees: 

code * FUN_004900fb(int param_1)

{
  int *piVar1;
  
  piVar1 = &DAT_0065eba8;
  while( true ) {
    if (*piVar1 == 0) {
      return FUN_0048fee9;
    }
    if (param_1 == *piVar1) break;
    piVar1 = piVar1 + 2;
  }
  return (code *)piVar1[1];
}

