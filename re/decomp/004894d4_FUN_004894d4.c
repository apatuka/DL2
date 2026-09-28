// FUN_004894d4 @ 004894d4 size=80 sig=undefined FUN_004894d4() cc=unknown
// callers: FUN_00489481
// callees: strlen,FUN_004a6964,FUN_00489320
// strings: \"\\\\Error opening, %s (%s)\\r\\n\"

void FUN_004894d4(char *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  iVar1 = strlen(param_1);
  pcVar3 = param_1 + iVar1;
  if (((*param_1 != '\0') && (((param_1[1] != ':' || (param_1[2] != '\0')) && (pcVar3[-1] != '/'))))
     && (pcVar3[-1] != '\\')) {
    *pcVar3 = s__Error_opening___s___s__0051b2a4[0];
    pcVar3 = pcVar3 + 1;
  }
  uVar2 = FUN_00489320(param_2);
  FUN_004a6964(pcVar3,uVar2);
  return;
}

