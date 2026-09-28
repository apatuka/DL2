// FUN_004a6918 @ 004a6918 size=75 sig=undefined FUN_004a6918() cc=unknown
// callers: FUN_004a950a
// callees: 

void FUN_004a6918(char *param_1,char *param_2)

{
  char *pcVar1;
  
  do {
    if ((*param_1 != *param_2) || (*param_2 == '\0')) {
      return;
    }
    if (param_1[1] != param_2[1]) {
      return;
    }
    if (param_2[1] == '\0') {
      return;
    }
    if (param_1[2] != param_2[2]) {
      return;
    }
    if (param_2[2] == '\0') {
      return;
    }
    pcVar1 = param_2 + 3;
    if (param_1[3] != *pcVar1) {
      return;
    }
    param_1 = param_1 + 4;
    param_2 = param_2 + 4;
  } while (*pcVar1 != '\0');
  return;
}

