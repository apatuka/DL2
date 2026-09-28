// FUN_00489356 @ 00489356 size=39 sig=undefined FUN_00489356() cc=unknown
// callers: FUN_00489481
// callees: 

undefined4 FUN_00489356(char *param_1)

{
  while( true ) {
    if (*param_1 == '\0') {
      return 0;
    }
    if (((*param_1 == '/') || (*param_1 == '\\')) || (*param_1 == ':')) break;
    param_1 = param_1 + 1;
  }
  return 1;
}

