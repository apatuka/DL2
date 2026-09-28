// FUN_0046237c @ 0046237c size=331 sig=undefined FUN_0046237c() cc=unknown
// callers: FUN_00465e7c,FUN_00462624
// callees: 

uint FUN_0046237c(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_1 != 0) && (param_3 != *(short *)(&DAT_005a0548 + param_1 * 10 + param_2 * 400))) {
    uVar1 = 2;
  }
  if ((param_2 != 0) && (param_3 != *(short *)(&DAT_005a03c2 + param_1 * 10 + param_2 * 400))) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 < 0x28) && (param_3 != (short)(&DAT_005a055c)[param_2 * 200 + param_1 * 5])) {
    uVar1 = uVar1 | 8;
  }
  if ((param_2 < 0x28) && (param_3 != (short)(&DAT_005a06e2)[param_2 * 200 + param_1 * 5])) {
    uVar1 = uVar1 | 4;
  }
  if (((param_1 != 0) && (param_2 != 0)) &&
     (param_3 != *(short *)(&DAT_005a03b8 + param_1 * 10 + param_2 * 400))) {
    uVar1 = uVar1 | 0x10;
  }
  if (((param_1 != 0) && (param_2 != 0x28)) &&
     (param_3 != *(short *)(&DAT_005a06d8 + param_1 * 10 + param_2 * 400))) {
    uVar1 = uVar1 | 0x40;
  }
  if (((param_1 != 0x28) && (param_2 != 0x28)) &&
     (param_3 != *(short *)(&DAT_005a06ec + param_1 * 10 + param_2 * 400))) {
    uVar1 = uVar1 | 0x80;
  }
  if (((param_1 != 0x28) && (param_2 != 0)) &&
     (param_3 != *(short *)(&DAT_005a03cc + param_1 * 10 + param_2 * 400))) {
    uVar1 = uVar1 | 0x20;
  }
  return uVar1;
}

