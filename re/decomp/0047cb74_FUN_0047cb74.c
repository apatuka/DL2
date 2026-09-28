// FUN_0047cb74 @ 0047cb74 size=609 sig=undefined FUN_0047cb74() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0047cb2c,FUN_0044bea8,FUN_0047ca98,FUN_004237d0,FUN_0046c9d8,FUN_00423690
// strings: \"Plague\"

void FUN_0047cb74(int param_1)

{
  uint *puVar1;
  short *psVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  bool bVar10;
  int local_14;
  ushort local_e;
  int local_c;
  
  bVar10 = *(int *)(param_1 + 8) < 0;
  if (bVar10) {
    *(int *)(param_1 + 8) = -*(int *)(param_1 + 8);
  }
  if (*(int *)(param_1 + 8) == 0) {
    if (DAT_0059f154 < 0x1a) {
      return;
    }
    iVar4 = FUN_0046c9d8((int)DAT_004d5b18,s_Plague_004dcad8);
    *(undefined **)(param_1 + 4) = &DAT_005a43d0 + (iVar4 + 1) * 0xadc;
    iVar4 = *(int *)(param_1 + 4);
    if ((((*(char *)(iVar4 + 0x20) == -1) || (*(char *)(iVar4 + 0x21) == '\0')) ||
        (*(short *)(iVar4 + 0x30) < 0x33)) || (iVar4 = FUN_0047cb2c(iVar4), iVar4 != 0)) {
      FUN_0047cb04(param_1);
      return;
    }
    iVar4 = FUN_0046c9d8(5,s_Plague_004dcad8);
    bVar10 = true;
    *(int *)(param_1 + 8) = iVar4 + 5;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  if (((*(short *)(*(int *)(param_1 + 4) + 0x30) < 0x32) || (*(int *)(param_1 + 8) == 0)) ||
     (iVar4 = FUN_0047cb2c(*(int *)(param_1 + 4)), iVar4 != 0)) {
    puVar1 = (uint *)(*(int *)(param_1 + 4) + 0x1c);
    *puVar1 = *puVar1 & 0xffffffdf;
    FUN_00423690((int)*(char *)(*(int *)(param_1 + 4) + 0x20),0x5e,*(undefined4 *)(param_1 + 4),0,0,
                 0);
    FUN_0047cb04(param_1);
  }
  else {
    iVar4 = *(int *)(param_1 + 4);
    puVar1 = (uint *)(iVar4 + 0x1c);
    *puVar1 = *puVar1 | 0x20;
    iVar4 = (int)*(short *)(iVar4 + 0x30) >> 2;
    psVar2 = (short *)(*(int *)(param_1 + 4) + 0x30);
    *psVar2 = *psVar2 - (short)iVar4;
    FUN_0044bea8(*(undefined4 *)(param_1 + 4));
    FUN_004237d0((int)*(char *)(*(int *)(param_1 + 4) + 0x20),0x5d,*(undefined4 *)(param_1 + 4),
                 iVar4,*(undefined4 *)(param_1 + 8),0,(int)*(short *)(*(int *)(param_1 + 4) + 0x1a),
                 0);
    if (!bVar10) {
      uVar5 = FUN_0046c9d8(100,s_Plague_004dcad8);
      bVar10 = 0x4b < uVar5;
      for (local_c = 0; (!bVar10 && (local_c < 7)); local_c = local_c + 1) {
        local_e = *(ushort *)(*(int *)(param_1 + 4) + 0x890 + local_c * 2);
        for (local_14 = 0; ((!bVar10 && (local_e != 0)) && (local_14 < 0x10));
            local_14 = local_14 + 1) {
          if ((local_e & 1) != 0) {
            iVar4 = local_c * 0x10 + local_14;
            piVar6 = &DAT_00654804;
            iVar8 = iVar4 * 0xadc;
            bVar3 = false;
            puVar9 = &DAT_005a43d0 + iVar8;
            iVar7 = 0;
            do {
              if ((*piVar6 == 1) && (puVar9 == (undefined *)piVar6[1])) {
                bVar3 = true;
                break;
              }
              iVar7 = iVar7 + 1;
              piVar6 = piVar6 + 7;
            } while (iVar7 < 0x32);
            if (((!bVar3) && ((&DAT_005a444e)[iVar8] != '\0')) &&
               (((*(byte *)((int)&DAT_005a43ec + iVar8 + 1) & 1) == 0 &&
                ((((*(byte *)(&DAT_005a43ec + iVar4 * 0x2b7) & 0x20) == 0 &&
                  ((&DAT_005a43f0)[iVar8] == *(char *)(*(int *)(param_1 + 4) + 0x20))) &&
                 (0x32 < (short)(&DAT_005a4400)[iVar4 * 0x56e])))))) {
              FUN_0047ca98(1,puVar9,-(*(int *)(param_1 + 8) + 1));
              if ((0x32 < (short)(&DAT_005a4400)[iVar4 * 0x56e]) &&
                 (iVar7 = FUN_0047cb2c(puVar9), iVar7 == 0)) {
                (&DAT_005a43ec)[iVar4 * 0x2b7] = (&DAT_005a43ec)[iVar4 * 0x2b7] | 0x20;
                FUN_00423690((int)(char)(&DAT_005a43f0)[iVar8],0x60,*(undefined4 *)(param_1 + 4),
                             puVar9,0,0);
              }
              bVar10 = true;
            }
          }
          local_e = (short)local_e >> 1;
        }
      }
    }
  }
  return;
}

