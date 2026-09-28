// FUN_00462914 @ 00462914 size=128 sig=undefined FUN_00462914() cc=unknown
// callers: FUN_00462994
// callees: 

undefined4 FUN_00462914(int param_1,int param_2,int param_3)

{
  short sVar1;
  undefined4 uVar2;
  
  param_2 = *(int *)(&DAT_004d1f08 + param_3 * 4) + param_2;
  param_1 = *(int *)(&DAT_004d1ef8 + param_3 * 4) + param_1;
  if ((((param_1 < 0) || (DAT_004d5b1a <= param_1)) || (param_2 < 0)) || (DAT_004d5b1b <= param_2))
  {
    uVar2 = 0xffffffff;
  }
  else {
    sVar1 = (&DAT_005a0552)[param_2 * 200 + param_1 * 5];
    uVar2 = CONCAT22((short)((uint)(param_1 * 5) >> 0x10),sVar1);
    if ((sVar1 != -1) && ((&DAT_005a444e)[sVar1 * 0xadc] == '0')) {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

