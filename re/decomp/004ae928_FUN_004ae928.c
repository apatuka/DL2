// FUN_004ae928 @ 004ae928 size=74 sig=undefined FUN_004ae928() cc=unknown
// callers: FUN_004ae974
// callees: FUN_004ad674

uint FUN_004ae928(short param_1,uint param_2,uint param_3)

{
  uint uVar1;
  short *psVar2;
  
  psVar2 = (short *)FUN_004ad674(0xe);
  if ((param_1 == 0x47) || (uVar1 = param_3, param_1 == 0x67)) {
    do {
      uVar1 = param_3;
      if (*(short *)(param_3 - 2) != 0x30) goto LAB_004ae95f;
      param_3 = param_3 - 2;
    } while (param_2 < param_3);
  }
  else {
LAB_004ae95f:
    param_2 = uVar1;
    if (*psVar2 == *(short *)(param_2 - 2)) {
      param_2 = param_2 - 2;
    }
  }
  return param_2;
}

