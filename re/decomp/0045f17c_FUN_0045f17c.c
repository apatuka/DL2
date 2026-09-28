// FUN_0045f17c @ 0045f17c size=151 sig=undefined FUN_0045f17c() cc=unknown
// callers: FUN_0044a3b0
// callees: timeGetTime,FUN_0045ab14,FUN_00480b80

void FUN_0045f17c(void)

{
  short sVar1;
  DWORD DVar2;
  DWORD DVar3;
  short *psVar4;
  short local_8;
  short sStack_6;
  
  psVar4 = &local_8;
  DVar2 = DAT_004d1c88;
  if (((DAT_004d1bf8 != 0) && (DVar3 = timeGetTime(), DVar2 = DVar3, DAT_004d1c88 != 0)) &&
     ((int)DAT_004d1c88 < (int)DVar3)) {
    sVar1 = (short)((int)(DVar3 - DAT_004d1c88) / 0x42);
    _local_8 = CONCAT22(8,sVar1);
    if (7 < sVar1) {
      psVar4 = &sStack_6;
    }
    sVar1 = *psVar4;
    _local_8 = CONCAT22(8,sVar1);
    DVar2 = DAT_004d1c88;
    if (sVar1 != 0) {
      DAT_004d1c88 = DVar3;
      if (DAT_004d59b4 != 0) {
        FUN_00480b80((int)sVar1);
        return;
      }
      DVar2 = DVar3;
      if (DAT_004d5ad0 == 0) {
        FUN_0045ab14((int)sVar1);
        DVar2 = DAT_004d1c88;
      }
    }
  }
  DAT_004d1c88 = DVar2;
  return;
}

