// FUN_0049f978 @ 0049f978 size=72 sig=undefined FUN_0049f978() cc=unknown
// callers: FUN_004a016e,FUN_004a08c5
// callees: FUN_004920d1

int FUN_0049f978(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if (1 < (byte)(*param_1 - 1U)) {
      if (*param_1 == '\r') {
        if (iVar3 < iVar2) {
          iVar3 = iVar2;
        }
        iVar2 = 0;
      }
      else {
        iVar1 = FUN_004920d1((int)*param_1);
        iVar2 = iVar2 + iVar1;
      }
    }
  }
  if (iVar3 < iVar2) {
    iVar3 = iVar2;
  }
  return iVar3;
}

