// FUN_0040e470 @ 0040e470 size=627 sig=undefined FUN_0040e470() cc=unknown
// callers: 
// callees: FUN_00446b3c,FUN_0040e284,FUN_0040bbf4,FUN_004412d4,FUN_0046ca40,FUN_0040e440

void FUN_0040e470(int param_1)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  short *psVar7;
  int iVar8;
  undefined4 *puVar9;
  uint local_14;
  int local_10;
  undefined4 *local_c;
  
  iVar8 = 0;
  sVar2 = *(short *)(param_1 + 10);
  iVar3 = (int)sVar2;
  local_c = (undefined4 *)0x0;
  local_10 = 0;
  piVar6 = (int *)(param_1 + 0x44);
  local_14 = 0;
  iVar4 = 0;
  do {
    if (*piVar6 != 0) {
      local_14 = local_14 + 1;
      iVar8 = iVar4;
    }
    iVar4 = iVar4 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar4 < 0x10);
  uVar5 = FUN_0046ca40();
  if ((local_14 < (uVar5 & 3) + 4) && ((local_14 < 4 || (*(int *)(param_1 + 0x18) < 5)))) {
    if (local_14 < 4) goto LAB_0040e6ad;
    iVar4 = FUN_0040e440((int)*(short *)(param_1 + 10),&DAT_00521bb4);
    if (iVar4 != 1) goto LAB_0040e6ad;
  }
  iVar4 = (int)DAT_004fb1cc;
  uVar5 = 1 << ((byte)sVar2 & 0x1f);
  if ((uVar5 & (int)DAT_004fc4a8) != 0) {
    iVar4 = iVar4 + 1;
  }
  if ((uVar5 & (int)DAT_004fbe04) != 0) {
    iVar4 = iVar4 + 1;
  }
  FUN_00446b3c(*(undefined4 *)(*(int *)(param_1 + 0x44 + iVar8 * 4) + 0x38),iVar4,3,
               (int)*(short *)(param_1 + 10),0x2000 << ((byte)*(short *)(param_1 + 10) & 0x1f));
  for (puVar9 = &DAT_005a4eac; puVar9 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar9 = puVar9 + 0x2b7) {
    if ((((*(char *)((int)puVar9 + 0x7e) != '\0') && ('\0' < *(char *)((int)puVar9 + iVar3 + 0x66)))
        && ((0x2000 << ((byte)*(undefined2 *)(param_1 + 10) & 0x1f) & puVar9[7]) != 0)) &&
       ((*(char *)(puVar9 + 8) != -1 && (*(char *)(puVar9 + 8) != iVar3)))) {
      iVar8 = FUN_004412d4(iVar3,(int)*(char *)(puVar9 + 8),0x10);
      if (iVar8 == 0) {
        iVar8 = 0;
        if (*(short *)(puVar9 + 0xc) != 0) {
          uVar5 = FUN_0046ca40();
          iVar8 = (uVar5 % 10 + 1) * local_14 - (int)*(short *)(puVar9 + 0xc) / 100;
        }
        bVar1 = *(byte *)(puVar9 + 8);
        if ((1 << (bVar1 & 0x1f) & *(uint *)(&DAT_0052222c + iVar3 * 4)) != 0) {
          iVar8 = iVar8 + 0x32;
        }
        if (DAT_004d5b00 == '\0') {
          iVar8 = iVar8 + (&DAT_0065e3cc)[(char)bVar1] * 10;
        }
        if (DAT_004d5b00 == '\x02') {
          iVar8 = iVar8 + (&DAT_0065e3e8)[(char)bVar1] * 10;
        }
        iVar4 = 0;
        psVar7 = (short *)((int)puVar9 + 0x9b6);
        do {
          if (iVar4 == 9) {
            iVar8 = iVar8 + *psVar7 * 0x32;
          }
          else if (iVar4 != 0x12) {
            iVar8 = iVar8 + *psVar7 * 0xf;
          }
          iVar4 = iVar4 + 1;
          psVar7 = psVar7 + 1;
        } while (iVar4 < 0x15);
        iVar8 = iVar8 + (int)*(short *)((int)puVar9 + 0x9da) * (int)*(short *)((int)puVar9 + 0x9da)
                        * -5;
        if (local_10 <= iVar8) {
          *(undefined4 **)(param_1 + 0x10) = puVar9;
          iVar4 = FUN_0040e284(param_1);
          if (iVar4 != 0) {
            local_10 = iVar8;
            local_c = puVar9;
          }
        }
      }
    }
  }
LAB_0040e6ad:
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  if (local_c == (undefined4 *)0x0) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  else {
    *(undefined4 **)(param_1 + 0x10) = local_c;
    FUN_0040bbf4(param_1,0,0);
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 1;
  }
  return;
}

