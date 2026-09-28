// FUN_004971d4 @ 004971d4 size=72 sig=undefined FUN_004971d4() cc=unknown
// callers: FUN_004976dc
// callees: FUN_0049716d

char * FUN_004971d4(char *param_1)

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
    if (((*param_1 == '#') || (*param_1 == '\r')) || (*param_1 == '\n')) {
      param_1 = (char *)FUN_0049716d(param_1);
    }
  }
  return param_1;
}

