// FUN_0040f794 @ 0040f794 size=129 sig=undefined FUN_0040f794() cc=unknown
// callers: FUN_0040b5cc,FUN_0040fb14,FUN_0040f974
// callees: FUN_00446b3c

bool FUN_0040f794(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  
  if ((param_2 == 0) || (param_3 == 0)) {
    bVar1 = true;
  }
  else {
    iVar3 = (int)(char)(&DAT_004faf8c)[param_4 * 0x24];
    bVar2 = (byte)param_1;
    if ((1 << (bVar2 & 0x1f) & (int)DAT_004fc4a8) != 0) {
      iVar3 = iVar3 + 1;
    }
    if ((1 << (bVar2 & 0x1f) & (int)DAT_004fbe04) != 0) {
      iVar3 = iVar3 + 1;
    }
    FUN_00446b3c(param_2,iVar3,3,param_1,0x2000 << (bVar2 & 0x1f));
    bVar1 = *(short *)(param_3 + 0xa70 + param_1 * 2) <= iVar3;
  }
  return bVar1;
}

