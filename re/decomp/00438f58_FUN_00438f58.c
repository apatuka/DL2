// FUN_00438f58 @ 00438f58 size=133 sig=undefined FUN_00438f58() cc=unknown
// callers: 
// callees: FUN_004a43da

uint FUN_00438f58(undefined4 param_1,int param_2,uint param_3,undefined4 param_4)

{
  if (param_2 == 0x30) {
    if (((((((param_3 != 0x10a) && (param_3 != 0x106)) && (param_3 != 0x102)) &&
          ((param_3 != 8 && (param_3 != 0x107)))) &&
         ((param_3 != 0x105 &&
          (((int)(param_3 & 0xfffbffff) < 0x30 || (0x39 < (int)(param_3 & 0xfffbffff))))))) &&
        (((int)(param_3 & 0xfffbffff) < 0x41 || (0x5a < (int)(param_3 & 0xfffbffff))))) &&
       (((int)(param_3 & 0xfffbffff) < 0x61 || (0x7a < (int)(param_3 & 0xfffbffff))))) {
      param_3 = 0;
    }
  }
  else {
    param_3 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return param_3;
}

