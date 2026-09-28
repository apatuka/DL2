// FUN_0040a420 @ 0040a420 size=221 sig=undefined FUN_0040a420() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040a14c,FUN_0040a2a4,FUN_0040a3c0,FUN_0040cdfc,FUN_00408f58

void FUN_0040a420(int param_1)

{
  int iVar1;
  
  iVar1 = (int)(char)(&DAT_0059f19e)[param_1 * 0x2d8];
  if ((iVar1 == 0) ||
     ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar1 * 0x19]) != 0)) {
    iVar1 = FUN_0040a3c0(param_1);
  }
  if (iVar1 != 0) {
    FUN_0040cdfc(param_1,4,(int)(char)(&DAT_0059f327)[param_1 * 0x2d8],iVar1,0);
  }
  if (*(int *)(&DAT_004d4f94 + DAT_004d5b1c * 0x14) < 100) {
    FUN_0040cdfc(param_1,4,50000,0xb,1);
  }
  if (*(int *)(&DAT_004d4f9c + DAT_004d5b1c * 0x14) < 100) {
    FUN_0040cdfc(param_1,4,50000,3,1);
  }
  FUN_0040a2a4(param_1);
  FUN_00408f58(param_1,4,0xfffff830,8,0);
  FUN_0040a14c(param_1,4,&DAT_004b65e8);
  return;
}

