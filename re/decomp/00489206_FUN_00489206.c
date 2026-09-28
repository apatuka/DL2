// FUN_00489206 @ 00489206 size=44 sig=undefined FUN_00489206() cc=unknown
// callers: FUN_00489232
// callees: FUN_0048f758

void FUN_00489206(int param_1)

{
  char *pcVar1;
  
  if ((*(byte *)(param_1 + 0x106) & 0x10) == 0) {
    pcVar1 = (char *)FUN_0048f758(param_1 + 0x132,0x2e);
    if (*pcVar1 == '\0') {
      *pcVar1 = '.';
      pcVar1[1] = '\0';
    }
  }
  return;
}

