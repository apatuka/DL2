// FUN_00489406 @ 00489406 size=96 sig=undefined FUN_00489406() cc=unknown
// callers: FUN_004988fc
// callees: strlen,FUN_004a6964
// strings: \"\\\\Error opening, %s (%s)\\r\\n\"

undefined4 FUN_00489406(char *param_1,undefined4 param_2,char param_3)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  iVar1 = strlen(param_1);
  pcVar3 = param_1 + iVar1;
  pcVar2 = pcVar3;
  do {
    pcVar2 = pcVar2 + -1;
    if (pcVar2 <= param_1) break;
    if (*pcVar2 == '.') {
      pcVar3 = pcVar2;
      if (param_3 == '\0') {
        return 0;
      }
      break;
    }
    if (*pcVar2 == '/') {
      s__Error_opening___s___s__0051b2a4[0] = '/';
      break;
    }
  } while (*pcVar2 != '\\');
  *pcVar3 = '.';
  FUN_004a6964(pcVar3 + 1,param_2);
  return 1;
}

