// FUN_00462ef0 @ 00462ef0 size=150 sig=undefined FUN_00462ef0() cc=unknown
// callers: 
// callees: 

void FUN_00462ef0(int param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  short *local_14;
  int local_8;
  
  local_8 = 0;
  local_14 = &DAT_005a0552;
  do {
    iVar2 = 0;
    psVar1 = local_14;
    do {
      if (param_1 == *psVar1) {
        *psVar1 = (short)param_2;
        (&DAT_005a444e)[param_1 * 0xadc] = (&DAT_005a444e)[param_1 * 0xadc] + -1;
        (&DAT_005a444e)[param_2 * 0xadc] = (&DAT_005a444e)[param_2 * 0xadc] + '\x01';
      }
      iVar2 = iVar2 + 1;
      psVar1 = psVar1 + 5;
    } while (iVar2 < 0x28);
    local_8 = local_8 + 1;
    local_14 = local_14 + 200;
  } while (local_8 < 0x28);
  return;
}

