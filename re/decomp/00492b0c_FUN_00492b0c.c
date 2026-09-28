// FUN_00492b0c @ 00492b0c size=59 sig=undefined FUN_00492b0c() cc=unknown
// callers: FUN_00493149,FUN_00492d67,FUN_0049331e
// callees: 

byte * FUN_00492b0c(byte *param_1)

{
  while( true ) {
    if (*param_1 == 0) {
      return param_1;
    }
    if ((*param_1 == 10) || (*param_1 == 0xd)) break;
    if (0x20 < *param_1) {
      return param_1;
    }
    param_1 = param_1 + 1;
  }
  if (((*param_1 == 10) && (param_1[1] == 0xd)) || ((*param_1 == 0xd && (param_1[1] == 10)))) {
    param_1 = param_1 + 1;
  }
  return param_1 + 1;
}

