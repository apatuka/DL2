// FUN_00440694 @ 00440694 size=389 sig=undefined FUN_00440694() cc=unknown
// callers: FUN_00440b68
// callees: FUN_00464498,FUN_00464444

void FUN_00440694(int param_1,int param_2,byte param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_3 & 4) != 0) {
    uVar4 = 0;
    do {
      pcVar1 = (char *)(param_4 + uVar4 + DAT_0058f138);
      iVar3 = (int)uVar4 >> 1;
      if (DAT_004d5ad4 == 2) {
        iVar2 = iVar3;
        if (iVar3 < 0) {
          iVar2 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        FUN_00464444(uVar4 + param_1,(iVar3 + param_2) - (int)*pcVar1,uVar4 + param_1 + 1,
                     (iVar2 + param_2) - (int)pcVar1[1],0);
      }
      else {
        iVar2 = iVar3;
        if (iVar3 < 0) {
          iVar2 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        FUN_00464498(uVar4 + param_1,(iVar3 + param_2) - (int)*pcVar1,uVar4 + param_1 + 1,
                     (iVar2 + param_2) - (int)pcVar1[1],0xff);
      }
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < 0x1f);
  }
  if ((param_3 & 8) != 0) {
    uVar4 = 0;
    do {
      pcVar1 = (char *)(((param_4 + 0x1f) - uVar4 * DAT_0058f140) + DAT_0058f138);
      iVar3 = (int)uVar4 >> 1;
      if (DAT_004d5ad4 == 2) {
        iVar2 = iVar3;
        if (iVar3 < 0) {
          iVar2 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        FUN_00464444(uVar4 + param_1 + 0x20,((param_2 + 0x10) - iVar3) - (int)*pcVar1,
                     uVar4 + param_1 + 0x21,((param_2 + 0x10) - iVar2) - (int)pcVar1[-DAT_0058f140],
                     0);
      }
      else {
        iVar2 = iVar3;
        if (iVar3 < 0) {
          iVar2 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        if (iVar3 < 0) {
          iVar3 = iVar3 + (uint)((uVar4 & 1) != 0);
        }
        FUN_00464498(uVar4 + param_1 + 0x20,((param_2 + 0x10) - iVar3) - (int)*pcVar1,
                     uVar4 + param_1 + 0x21,((param_2 + 0x10) - iVar2) - (int)pcVar1[-DAT_0058f140],
                     0xff);
      }
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < 0x1f);
  }
  return;
}

