// FUN_0049753f @ 0049753f size=98 sig=undefined FUN_0049753f() cc=unknown
// callers: 
// callees: 

byte * FUN_0049753f(byte *param_1,byte *param_2,char param_3)

{
  byte *pbVar1;
  
  if (param_1 == (byte *)0x0) {
    *param_2 = 0;
  }
  else {
    for (; ((*param_1 == 0x20 || (*param_1 == 9)) || (pbVar1 = param_1, *param_1 == 0x3d));
        param_1 = param_1 + 1) {
    }
    for (; (((*pbVar1 != 0x20 && (*pbVar1 != 0x3d)) &&
            ((*pbVar1 != 9 && ((*pbVar1 != 0xd && (*pbVar1 != 0)))))) &&
           ((uint)*pbVar1 != (int)param_3)); pbVar1 = pbVar1 + 1) {
      *param_2 = *pbVar1;
      param_2 = param_2 + 1;
    }
    *param_2 = 0;
  }
  return param_1;
}

