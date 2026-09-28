// FUN_0048447c @ 0048447c size=99 sig=undefined FUN_0048447c() cc=unknown
// callers: FUN_00487820,FUN_00480150,DrawSTileBuilding
// callees: FUN_00492290,FUN_00484460

void FUN_0048447c(char *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  FUN_00484460(param_1);
  while (*param_1 != '\0') {
    iVar2 = 0;
    pcVar3 = (char *)0x0;
    for (; (iVar2 < param_2 && (*param_1 != '\0')); param_1 = param_1 + 1) {
      iVar1 = FUN_00492290(*param_1);
      iVar2 = iVar2 + iVar1;
      if (*param_1 == ' ') {
        pcVar3 = param_1;
      }
    }
    if (param_2 <= iVar2) {
      if (pcVar3 == (char *)0x0) {
        if (*param_1 == ' ') {
          *param_1 = '\n';
        }
      }
      else {
        *pcVar3 = '\n';
        param_1 = pcVar3 + 1;
      }
    }
  }
  return;
}

