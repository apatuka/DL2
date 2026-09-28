// FUN_00489232 @ 00489232 size=96 sig=undefined FUN_00489232() cc=unknown
// callers: FUN_00438b9c,FUN_004397a0
// callees: FUN_00489206,FindNextFileA,FUN_00489159

char * FUN_00489232(char *param_1)

{
  char cVar1;
  BOOL BVar2;
  
  do {
    if ((*param_1 == '\0') &&
       (BVar2 = FindNextFileA(*(HANDLE *)(param_1 + 0x244),(LPWIN32_FIND_DATAA)(param_1 + 0x106)),
       BVar2 == 0)) {
      return (char *)0x0;
    }
    *param_1 = '\0';
    if (param_1[1] != '\0') {
      FUN_00489206(param_1);
    }
    cVar1 = FUN_00489159(param_1 + 0x132,param_1 + 2);
  } while (cVar1 == '\0');
  if (param_1[1] == '\0') {
    FUN_00489206(param_1);
  }
  return param_1 + 0x132;
}

