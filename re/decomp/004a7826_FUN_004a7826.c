// FUN_004a7826 @ 004a7826 size=126 sig=undefined FUN_004a7826() cc=unknown
// callers: FUN_004a8c58
// callees: __assertfail
// strings: \"XX.CPP\"|\"(mfnMask & 0x0080) == 0\"|\"what?\"|\"!\\\"what?\\\"\"

void FUN_004a7826(undefined4 param_1,code *param_2,uint param_3)

{
  if ((param_3 & 0x80) != 0) {
    __assertfail(s__mfnMask___0x0080_____0_0051f31a,s_XX_CPP_0051f332,0x2da);
  }
  param_3 = param_3 & 7;
  if (param_3 == 1) {
    (*param_2)(param_1);
    return;
  }
  if (param_3 == 2) {
    (*param_2)(param_1);
    return;
  }
  if (param_3 == 3) {
    (*param_2)();
    return;
  }
  if (param_3 == 5) {
    (*param_2)(param_1);
    return;
  }
  __assertfail(s___what___0051f33f,s_XX_CPP_0051f348,0x301);
  return;
}

