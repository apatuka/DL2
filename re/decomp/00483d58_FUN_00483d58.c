// FUN_00483d58 @ 00483d58 size=455 sig=undefined FUN_00483d58() cc=unknown
// callers: FUN_00485668,FUN_0047c730,FindArtifact,@CheatTechDialog$qqspvuiuil,FUN_00431f6c,FUN_0046c49c,FUN_00484114,FUN_0043cc5c,FUN_00473280,FUN_0047323c
// callees: FUN_0044d1a4,FUN_00483bd4,FUN_00457ac0,FUN_00450150,FUN_0048389c

void FUN_00483d58(int param_1,ushort *param_2)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  uint uVar6;
  undefined4 *puVar7;
  int local_c;
  
  uVar6 = 1 << ((byte)param_1 & 0x1f);
  if (((int)(short)*param_2 & uVar6) == 0) {
    if (param_2 == &DAT_004fc21e) {
      for (puVar7 = &DAT_005a4eac; puVar7 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar7 = puVar7 + 0x2b7) {
        iVar4 = FUN_0044d1a4(puVar7,0xb,0);
        if (iVar4 == -1) {
          puVar7[param_1 + 0x25e] = 0;
        }
        else {
          puVar7[0x22c] = puVar7[0x22c] | 1 << ((byte)param_1 & 0x1f);
          puVar7[param_1 + 0x25e] = 1;
        }
      }
    }
    uVar2 = (ushort)uVar6;
    *param_2 = *param_2 | uVar2;
    param_2[1] = param_2[1] & ~uVar2;
    if (param_1 == DAT_0058f1f4) {
      FUN_00483bd4(param_2);
    }
    uVar3 = FUN_0048389c();
    local_c = 1;
    do {
      if (((((int)(short)(&DAT_004fbbac)[local_c * 0x19] & uVar6) == 0) &&
          (iVar4 = (*(code *)PTR_FUN_004d02b8)(3), (short)(&DAT_004fbbcc)[local_c * 0x19] < iVar4))
         && (iVar4 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],local_c), iVar4 != 0))
      {
        bVar1 = true;
        iVar4 = 0;
        psVar5 = (short *)(&DAT_004fbbd0 + local_c * 0x32);
        do {
          if (*psVar5 != 0) {
            if (((int)(short)(&DAT_004fbbac)[*psVar5 * 0x19] & uVar6) == 0) {
              bVar1 = false;
            }
            else if ((uVar3 & uVar6) != 0) {
              (&DAT_004fbbae)[local_c * 0x19] = (&DAT_004fbbae)[local_c * 0x19] | uVar2;
            }
          }
          iVar4 = iVar4 + 1;
          psVar5 = psVar5 + 1;
        } while (iVar4 < 4);
        if (bVar1) {
          (&DAT_004fbbae)[local_c * 0x19] = (&DAT_004fbbae)[local_c * 0x19] | uVar2;
        }
      }
      local_c = local_c + 1;
    } while (local_c < 0x2f);
    if ((((int)DAT_004fc4da & uVar6) == 0) &&
       (iVar4 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],0x2f), iVar4 != 0)) {
      iVar4 = 1;
      psVar5 = &DAT_004fbbde;
      do {
        if (((int)*psVar5 & uVar6) == 0) {
          return;
        }
        iVar4 = iVar4 + 1;
        psVar5 = psVar5 + 0x19;
      } while (iVar4 < 0x2f);
      DAT_004fc4dc = DAT_004fc4dc | uVar2;
    }
  }
  return;
}

