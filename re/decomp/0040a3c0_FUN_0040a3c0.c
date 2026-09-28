// FUN_0040a3c0 @ 0040a3c0 size=96 sig=undefined FUN_0040a3c0() cc=unknown
// callers: FUN_0040a420
// callees: FUN_0040a37c,FUN_00483cbc

int FUN_0040a3c0(int param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  
  psVar3 = &DAT_004fbbe0;
  iVar2 = 1;
  while (((1 << ((byte)param_1 & 0x1f) & (int)*psVar3) == 0 ||
         (iVar1 = FUN_0040a37c(param_1,iVar2), iVar1 != 0))) {
    iVar2 = iVar2 + 1;
    psVar3 = psVar3 + 0x19;
    if (0x2f < iVar2) {
      iVar2 = FUN_00483cbc(&DAT_0059f160 + param_1 * 0x2d8,1);
      return iVar2;
    }
  }
  return iVar2;
}

