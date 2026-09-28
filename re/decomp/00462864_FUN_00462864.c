// FUN_00462864 @ 00462864 size=175 sig=undefined FUN_00462864() cc=unknown
// callers: FUN_00462994
// callees: FUN_004ae5d8

short FUN_00462864(int param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  
  param_1 = *(int *)(&DAT_004d1ef8 + param_3 * 4) + param_1;
  param_2 = *(int *)(&DAT_004d1f08 + param_3 * 4) + param_2;
  if ((((param_1 < 0) || (DAT_004d5b1a <= param_1)) || (param_2 < 0)) || (DAT_004d5b1b <= param_2))
  {
    sVar1 = -1;
  }
  else {
    sVar1 = (&DAT_005a0552)[param_2 * 200 + param_1 * 5];
    if (sVar1 != -1) {
      if (((char)(&DAT_005a444e)[sVar1 * 0xadc] < '\x1d') ||
         (iVar2 = FUN_004ae5d8(), iVar2 % 6 == 0)) {
        if ((&DAT_005a444e)[sVar1 * 0xadc] == '0') {
          sVar1 = -1;
        }
      }
      else {
        sVar1 = -1;
      }
    }
  }
  return sVar1;
}

