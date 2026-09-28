// FUN_004aff84 @ 004aff84 size=80 sig=undefined FUN_004aff84() cc=unknown
// callers: FUN_004b1fb4
// callees: 

byte * FUN_004aff84(byte *param_1,uint param_2)

{
  do {
    if (((&DAT_0069f56d)[*param_1] & 4) == 0) {
      if (param_2 == *param_1) {
        return param_1;
      }
      if (*param_1 == 0) {
        return (byte *)0x0;
      }
    }
    else {
      if (param_1[1] == 0) {
        if (param_2 != 0) {
          return (byte *)0x0;
        }
        return param_1 + 1;
      }
      if (param_2 == CONCAT11(*param_1,param_1[1])) {
        return param_1;
      }
      param_1 = param_1 + 1;
    }
    param_1 = param_1 + 1;
  } while( true );
}

