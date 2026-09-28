// FUN_00497293 @ 00497293 size=171 sig=undefined FUN_00497293() cc=unknown
// callers: 
// callees: 

byte * FUN_00497293(byte *param_1,char param_2)

{
  if (param_1 == (byte *)0x0) {
    param_1 = (byte *)0x0;
  }
  else {
    if ((((*param_1 == 0x20) || (*param_1 == 9)) || (*param_1 == 0x3d)) ||
       ((uint)*param_1 == (int)param_2)) {
      for (; ((*param_1 == 0x20 || (*param_1 == 9)) ||
             ((*param_1 == 0x3d || ((uint)*param_1 == (int)param_2)))); param_1 = param_1 + 1) {
      }
    }
    else {
      for (; ((*param_1 != 0x20 && (*param_1 != 0xd)) &&
             ((*param_1 != 9 &&
              (((*param_1 != 0 && (*param_1 != 0x3d)) && ((uint)*param_1 != (int)param_2))))));
          param_1 = param_1 + 1) {
      }
      for (; (((*param_1 == 0x20 || (*param_1 == 9)) || (*param_1 == 0x3d)) ||
             ((uint)*param_1 == (int)param_2)); param_1 = param_1 + 1) {
      }
    }
    if (((*param_1 == 0) || (*param_1 == 0x23)) || ((*param_1 == 0xd || (*param_1 == 10)))) {
      param_1 = (byte *)0x0;
    }
  }
  return param_1;
}

