// FUN_00489320 @ 00489320 size=54 sig=undefined FUN_00489320() cc=unknown
// callers: FUN_00489466,FUN_0048937d,FUN_004894d4,FUN_004893dd,FUN_004893b4
// callees: strlen
// strings: \"\\\\Error opening, %s (%s)\\r\\n\"

char * FUN_00489320(char *param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  iVar1 = strlen(param_1);
  pcVar2 = param_1 + iVar1;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + -1;
    if (((pcVar2 < param_1) || (*pcVar2 == ':')) || (*pcVar2 == '/')) break;
  } while (*pcVar2 != '\\');
  if (*pcVar2 == '/') {
    s__Error_opening___s___s__0051b2a4[0] = '/';
  }
  return pcVar3;
}

