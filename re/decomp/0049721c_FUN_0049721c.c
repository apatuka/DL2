// FUN_0049721c @ 0049721c size=119 sig=undefined FUN_0049721c() cc=unknown
// callers: FUN_004978f7,FUN_00497956
// callees: 

char * FUN_0049721c(char *param_1)

{
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    if (((*param_1 == ' ') || (*param_1 == '\t')) || (*param_1 == '=')) {
      for (; ((*param_1 == ' ' || (*param_1 == '\t')) || (*param_1 == '=')); param_1 = param_1 + 1)
      {
      }
    }
    else {
      for (; ((*param_1 != ' ' && (*param_1 != '\r')) &&
             ((*param_1 != '\t' && ((*param_1 != '\0' && (*param_1 != '='))))));
          param_1 = param_1 + 1) {
      }
      for (; (*param_1 == ' ' || ((*param_1 == '\t' || (*param_1 == '=')))); param_1 = param_1 + 1)
      {
      }
    }
    if ((((*param_1 == '\0') || (*param_1 == '#')) || (*param_1 == '\r')) || (*param_1 == '\n')) {
      param_1 = (char *)0x0;
    }
  }
  return param_1;
}

