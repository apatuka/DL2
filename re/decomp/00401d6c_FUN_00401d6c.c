// FUN_00401d6c @ 00401d6c size=190 sig=undefined FUN_00401d6c() cc=unknown
// callers: FUN_00402df4
// callees: 

int FUN_00401d6c(byte *param_1,int param_2,undefined4 param_3,int *param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  short *psVar3;
  
  if ((param_4[0xc] == 0) ||
     (((int)(short)(&DAT_004fbbac)[param_4[0xc] * 0x19] & 1 << (*param_1 & 0x1f)) != 0)) {
    if (param_2 == 0) {
      iVar1 = 0;
      param_1 = param_1 + 0xc;
      do {
        param_4 = param_4 + 1;
        if (*(int *)param_1 < *param_4) {
          return 1 << ((byte)iVar1 & 0x1f);
        }
        iVar1 = iVar1 + 1;
        param_1 = param_1 + 4;
      } while (iVar1 < 0xb);
    }
    else {
      iVar1 = 0;
      piVar2 = &DAT_00522018;
      psVar3 = (short *)(param_2 + 0x12);
      do {
        param_4 = param_4 + 1;
        if ((int)*psVar3 + *piVar2 < *param_4) {
          return 1 << ((byte)iVar1 & 0x1f);
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
        psVar3 = psVar3 + 1;
      } while (iVar1 < 0xb);
    }
    if (*(short *)(param_2 + 0x42) < param_5) {
      iVar1 = 0x800;
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 0x1000;
  }
  return iVar1;
}

