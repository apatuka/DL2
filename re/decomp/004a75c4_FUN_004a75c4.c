// FUN_004a75c4 @ 004a75c4 size=270 sig=undefined FUN_004a75c4() cc=unknown
// callers: FUN_004a7df4,FUN_004a78a4
// callees: __assertfail
// strings: \"XX.CPP\"|\"(ctorMask & 0x0100) != 0 || (ctorMask & 0x0020) == 0\"|\"(ctorMask & 0x0080) == 0\"|\"what?\"|\"!\\\"what?\\\"\"

void FUN_004a75c4(undefined4 param_1,undefined4 param_2,code *param_3,uint param_4)

{
  if (((param_4 & 0x100) == 0) && ((param_4 & 0x20) != 0)) {
    __assertfail(s__ctorMask___0x0100_____0_____cto_0051f25c,s_XX_CPP_0051f291,0x1e1);
  }
  if ((param_4 & 0x80) != 0) {
    __assertfail(s__ctorMask___0x0080_____0_0051f298,s_XX_CPP_0051f2b1,0x1e3);
  }
  if ((param_4 & 0x1000) == 0) {
    param_4 = param_4 & 7;
    if (param_4 == 1) {
      (*param_3)(param_1,param_2);
    }
    else if (param_4 == 2) {
      (*param_3)(param_2,param_1);
    }
    else if (param_4 == 3) {
      (*param_3)();
    }
    else if (param_4 == 5) {
      (*param_3)(param_1,param_2);
    }
    else {
      __assertfail(s___what___0051f2d4,s_XX_CPP_0051f2dd,0x23a);
    }
  }
  else {
    param_4 = param_4 & 7;
    if (param_4 == 1) {
      (*param_3)(param_1,0,param_2);
    }
    else if (param_4 == 2) {
      (*param_3)(param_1,param_2,0);
    }
    else if (param_4 == 3) {
      (*param_3)();
    }
    else if (param_4 == 5) {
      (*param_3)(param_1,0,param_2);
    }
    else {
      __assertfail(s___what___0051f2be,s_XX_CPP_0051f2c7,0x20e);
    }
  }
  return;
}

