// FUN_0040a1c0 @ 0040a1c0 size=227 sig=undefined FUN_0040a1c0() cc=unknown
// callers: FUN_0040a1c0,FUN_0040cea4
// callees: FUN_0040a1c0

int FUN_0040a1c0(undefined4 param_1,int param_2)

{
  short *psVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  bVar2 = (byte)param_1;
  if ((DAT_004fbe88 < (short)(&DAT_004fbbcc)[param_2 * 0x19]) &&
     ((1 << (bVar2 & 0x1f) & (uint)(DAT_004fbe68 == 0)) != 0)) {
    param_2 = 0xe;
  }
  else if ((DAT_004fc1a8 < (short)(&DAT_004fbbcc)[param_2 * 0x19]) &&
          ((1 << (bVar2 & 0x1f) & (uint)(DAT_004fc188 == 0)) != 0)) {
    param_2 = 0x1e;
  }
  if ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbae)[param_2 * 0x19]) == 0) {
    iVar3 = 0;
    psVar1 = (short *)(&DAT_004fbbd0 + param_2 * 0x32);
    do {
      iVar4 = (int)*psVar1;
      if ((iVar4 != 0) && ((1 << (bVar2 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar4 * 0x19]) == 0))
      {
        iVar3 = FUN_0040a1c0(param_1,iVar4);
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      psVar1 = psVar1 + 1;
    } while (iVar3 < 4);
    param_2 = 0;
  }
  return param_2;
}

