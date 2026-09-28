// FUN_004affd4 @ 004affd4 size=85 sig=undefined FUN_004affd4() cc=unknown
// callers: FUN_004b1c4c
// callees: 

byte * FUN_004affd4(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  
  if (((param_1 != (byte *)0x0) && (param_2 != (byte *)0x0)) && (param_1 < param_2)) {
    if (((&DAT_0069f56d)[param_2[-1]] & 4) == 0) {
      pbVar1 = param_2 + -2;
      while ((param_1 <= pbVar1 && (((&DAT_0069f56d)[*pbVar1] & 4) != 0))) {
        pbVar1 = pbVar1 + -1;
      }
      return param_2 + (-1 - ((int)param_2 - (int)pbVar1 & 1U));
    }
    return param_2 + -2;
  }
  return (byte *)0x0;
}

