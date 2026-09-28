// FUN_00483f20 @ 00483f20 size=350 sig=undefined FUN_00483f20() cc=unknown
// callers: FUN_0043cb7c,FUN_0043cc5c
// callees: FUN_00457ac0,FUN_00450150,FUN_0048389c

void FUN_00483f20(int param_1,ushort *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  short *psVar4;
  ushort uVar5;
  uint uVar6;
  int local_c;
  
  uVar6 = 1 << ((byte)param_1 & 0x1f);
  if (((int)(short)*param_2 & uVar6) != 0) {
    uVar5 = (ushort)uVar6;
    *param_2 = *param_2 & ~uVar5;
    uVar2 = FUN_0048389c();
    local_c = 1;
    do {
      if (((((int)(short)(&DAT_004fbbac)[local_c * 0x19] & uVar6) == 0) &&
          (iVar3 = (*(code *)PTR_FUN_004d02b8)(3), (short)(&DAT_004fbbcc)[local_c * 0x19] < iVar3))
         && (iVar3 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],local_c), iVar3 != 0))
      {
        psVar4 = (short *)(&DAT_004fbbd0 + local_c * 0x32);
        bVar1 = true;
        (&DAT_004fbbae)[local_c * 0x19] = (&DAT_004fbbae)[local_c * 0x19] & ~uVar5;
        iVar3 = 0;
        do {
          if (*psVar4 != 0) {
            if (((int)(short)(&DAT_004fbbac)[*psVar4 * 0x19] & uVar6) == 0) {
              bVar1 = false;
            }
            else if ((uVar2 & uVar6) != 0) {
              (&DAT_004fbbae)[local_c * 0x19] = (&DAT_004fbbae)[local_c * 0x19] | uVar5;
            }
          }
          iVar3 = iVar3 + 1;
          psVar4 = psVar4 + 1;
        } while (iVar3 < 4);
        if (bVar1) {
          (&DAT_004fbbae)[local_c * 0x19] = (&DAT_004fbbae)[local_c * 0x19] | uVar5;
        }
      }
      local_c = local_c + 1;
    } while (local_c < 0x2f);
    if ((((int)DAT_004fc4da & uVar6) == 0) &&
       (iVar3 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],0x2f), iVar3 != 0)) {
      iVar3 = 1;
      psVar4 = &DAT_004fbbde;
      do {
        if (((int)*psVar4 & uVar6) == 0) {
          return;
        }
        iVar3 = iVar3 + 1;
        psVar4 = psVar4 + 0x19;
      } while (iVar3 < 0x2f);
      DAT_004fc4dc = DAT_004fc4dc | uVar5;
      return;
    }
    DAT_004fc4dc = DAT_004fc4dc & ~uVar5;
  }
  return;
}

