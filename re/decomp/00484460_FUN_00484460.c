// FUN_00484460 @ 00484460 size=27 sig=undefined FUN_00484460() cc=unknown
// callers: FUN_0048447c
// callees: 

void FUN_00484460(char *param_1)

{
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if (*param_1 == '\n') {
      *param_1 = ' ';
    }
  }
  return;
}

