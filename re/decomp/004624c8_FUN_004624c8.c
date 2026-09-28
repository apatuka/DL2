// FUN_004624c8 @ 004624c8 size=180 sig=undefined FUN_004624c8() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004624c8(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((param_1 == 0) || (param_3 != *(short *)(&DAT_005a0548 + param_1 * 10 + param_2 * 400))) {
    if ((param_2 == 0) || (param_3 != *(short *)(&DAT_005a03c2 + param_1 * 10 + param_2 * 400))) {
      if ((param_1 == 0x28) || (param_3 != (short)(&DAT_005a055c)[param_2 * 200 + param_1 * 5])) {
        if ((param_2 != 0x28) && (param_3 == (short)(&DAT_005a06e2)[param_2 * 200 + param_1 * 5])) {
          uVar1 = 4;
        }
      }
      else {
        uVar1 = 8;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

