// FUN_004976b3 @ 004976b3 size=41 sig=undefined FUN_004976b3() cc=unknown
// callers: 
// callees: 

char * FUN_004976b3(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 0) {
    pcVar1 = (char *)0x0;
  }
  else {
    pcVar1 = (char *)(param_1 + 1);
    if ((((*pcVar1 == '\0') || (*pcVar1 == '#')) || (*pcVar1 == '\r')) || (*pcVar1 == '\n')) {
      pcVar1 = (char *)0x0;
    }
  }
  return pcVar1;
}

