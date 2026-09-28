// FUN_0048f758 @ 0048f758 size=28 sig=undefined FUN_0048f758() cc=unknown
// callers: FUN_00489206,FUN_004893b4,FUN_004893dd
// callees: 

char * FUN_0048f758(char *param_1,char param_2)

{
  char *pcVar1;
  
  do {
    pcVar1 = param_1;
    if (*pcVar1 == param_2) {
      return pcVar1;
    }
    param_1 = pcVar1 + 1;
  } while (*pcVar1 != '\0');
  return pcVar1;
}

