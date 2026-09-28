// FUN_00483a30 @ 00483a30 size=339 sig=undefined FUN_00483a30() cc=unknown
// callers: FUN_0043c540,FUN_00483b84,FUN_0043cc5c
// callees: FUN_00457ac0,FUN_00450150,FUN_0048389c

bool FUN_00483a30(int param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  short *psVar3;
  byte bVar4;
  bool bVar5;
  int local_10;
  int local_c;
  
  bVar4 = (byte)param_1;
  if ((1 << (bVar4 & 0x1f) & (int)(short)(&DAT_004fbbae)[param_3 * 0x19]) == 0) {
    if (((((1 << (bVar4 & 0x1f) & (int)(short)(&DAT_004fbbac)[param_3 * 0x19]) == 0) &&
         (iVar1 = (*(code *)PTR_FUN_004d02b8)(3), (short)(&DAT_004fbbcc)[param_3 * 0x19] < iVar1))
        && (param_3 != 0x2f)) &&
       (iVar1 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],param_3), iVar1 != 0)) {
      uVar2 = FUN_0048389c();
      local_c = 0;
      local_10 = 0;
      iVar1 = 0;
      psVar3 = (short *)(&DAT_004fbbd0 + param_3 * 0x32);
      do {
        if ((*psVar3 != 0) &&
           ((1 << (bVar4 & 0x1f) & (int)(short)(&DAT_004fbbac)[*psVar3 * 0x19]) == 0)) {
          local_c = local_c + 1;
        }
        iVar1 = iVar1 + 1;
        psVar3 = psVar3 + 1;
      } while (iVar1 < 4);
      for (; param_2 != (int *)0x0; param_2 = (int *)param_2[1]) {
        iVar1 = 0;
        psVar3 = (short *)(&DAT_004fbbd0 + param_3 * 0x32);
        do {
          if ((int)*psVar3 == *param_2) {
            if ((uVar2 & 1 << (bVar4 & 0x1f)) != 0) {
              return true;
            }
            local_10 = local_10 + 1;
          }
          iVar1 = iVar1 + 1;
          psVar3 = psVar3 + 1;
        } while (iVar1 < 4);
      }
      bVar5 = local_10 == local_c;
    }
    else {
      bVar5 = false;
    }
  }
  else {
    bVar5 = true;
  }
  return bVar5;
}

