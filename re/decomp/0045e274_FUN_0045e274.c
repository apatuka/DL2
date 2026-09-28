// FUN_0045e274 @ 0045e274 size=289 sig=undefined FUN_0045e274() cc=unknown
// callers: FUN_0045d478,FUN_0046f5d4,FUN_0045e7a4,FUN_0045ac80,FUN_00437134,FUN_0045e8e8,FUN_0045e99c,FUN_00421828
// callees: FUN_0045dfd4,FUN_0045e0b4,FUN_00418e00,FUN_0045ab1c,FUN_0045e13c,FUN_00440f64

void FUN_0045e274(int param_1,int param_2)

{
  short sVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (((DAT_004d59b4 != 0) && (DAT_004d59b4 != 0xb)) && (DAT_004d59b4 != 0x32)) {
    if (DAT_004d59b4 != 0x22) {
      return;
    }
    cVar2 = FUN_00418e00();
    if (cVar2 == '\0') {
      return;
    }
  }
  sVar1 = (&DAT_005a0552)[param_2 * 200 + param_1 * 5];
  if (DAT_004d5ad0 == 0) {
    FUN_0045ab1c(DAT_004d5acc);
    iVar5 = (int)DAT_005644c4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((DAT_005644c4 & 1) != 0);
    }
    iVar3 = (int)DAT_005644c8 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((DAT_005644c8 & 1) != 0);
    }
    FUN_0045e0b4(*(char *)(&DAT_005a4450)[sVar1 * 0x2b7] - iVar5,
                 *(char *)((&DAT_005a4450)[sVar1 * 0x2b7] + 1) - iVar3);
  }
  else {
    FUN_00440f64();
    iVar5 = (int)DAT_00559df8 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((DAT_00559df8 & 1) != 0);
    }
    if (iVar5 < 0) {
      iVar5 = iVar5 + 0x1f;
    }
    iVar3 = param_2 + param_1 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((param_2 + param_1 & 1U) != 0);
    }
    iVar4 = (int)DAT_00559dfc >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((DAT_00559dfc & 1) != 0);
    }
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0x1f;
    }
    FUN_0045e13c((param_1 - param_2) - (iVar5 >> 5),iVar3 - (iVar4 >> 5));
  }
  FUN_0045dfd4((int)(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5],1);
  return;
}

