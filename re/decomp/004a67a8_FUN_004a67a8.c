// FUN_004a67a8 @ 004a67a8 size=30 sig=undefined FUN_004a67a8() cc=unknown
// callers: FUN_004ac414,FUN_004ac2cc,FUN_004a9d10,FUN_004ac260
// callees: 

char * FUN_004a67a8(char *param_1,char param_2,int param_3)

{
  char *pcVar1;
  undefined1 in_ZF;
  
  if (param_3 != 0) {
    do {
      pcVar1 = param_1;
      if (param_3 == 0) break;
      param_3 = param_3 + -1;
      pcVar1 = param_1 + 1;
      in_ZF = param_2 == *param_1;
      param_1 = pcVar1;
    } while (!(bool)in_ZF);
    if ((bool)in_ZF) {
      return pcVar1 + -1;
    }
  }
  return (char *)0x0;
}

