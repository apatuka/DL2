// FUN_0040a338 @ 0040a338 size=67 sig=undefined FUN_0040a338() cc=unknown
// callers: FUN_0040cea4
// callees: 

undefined4 FUN_0040a338(byte param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  
  psVar2 = &DAT_004fbbe0;
  iVar1 = 1;
  while (((1 << (param_1 & 0x1f) & (int)*psVar2) == 0 || (iVar1 == param_2))) {
    iVar1 = iVar1 + 1;
    psVar2 = psVar2 + 0x19;
    if (0x2f < iVar1) {
      return 1;
    }
  }
  return 0;
}

