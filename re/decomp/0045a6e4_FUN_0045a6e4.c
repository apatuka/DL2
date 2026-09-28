// FUN_0045a6e4 @ 0045a6e4 size=445 sig=undefined FUN_0045a6e4() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: FUN_0046d250,BlitSprite8,FUN_00459ee0,FUN_0048477c,FUN_0043ee40

void FUN_0045a6e4(int param_1)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  undefined1 local_98 [32];
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64 [10];
  int local_3c [10];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  piVar3 = &DAT_004c5ab8;
  piVar4 = &DAT_004d1b88;
  piVar5 = local_3c;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  piVar4 = &DAT_004d1bb0;
  piVar5 = local_64;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  piVar4 = local_3c;
  piVar5 = local_64;
  pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x75) * 4);
  local_8 = (int)*pcVar1;
  local_c = (int)pcVar1[1];
  local_68 = 0;
  do {
    local_6c = *piVar3;
    local_70 = piVar3[1];
    if (DAT_004d5ad0 == 0) {
      FUN_00459ee0(*piVar4 + local_8,*piVar5 + local_c,&local_10,&local_14);
      local_74 = local_10 + 0x10;
      local_78 = local_14 + 0x20;
    }
    else {
      FUN_0043ee40(*piVar4 + local_8,*piVar5 + local_c,&local_10,&local_14);
      local_74 = local_10;
      local_78 = local_14;
      local_10 = local_10 + -0x10;
      local_14 = local_14 + -0x20;
    }
    if (*(int *)(param_1 + 0x3a + local_6c * 4) != 0) {
      iVar2 = local_70 * 0x10;
      BlitSprite8(*(undefined4 *)(&DAT_004e2b34 + iVar2),
                  *(short *)(&DAT_004e2b2c + iVar2) + local_74,
                  *(short *)(&DAT_004e2b2e + iVar2) + local_78,
                  (int)*(short *)(&DAT_004e2b30 + iVar2),(int)*(short *)(&DAT_004e2b32 + iVar2),
                  (int)*(short *)(&DAT_004e2b30 + iVar2),0);
      if ((local_68 == 1) && ((*(byte *)(param_1 + 0x1c) & 0x40) != 0)) {
        BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x48),
                    *(short *)(PTR_DAT_004d0384 + 0x40) + local_74 + -0x20,
                    *(short *)(PTR_DAT_004d0384 + 0x42) + local_78 + -0x10,
                    (int)*(short *)(PTR_DAT_004d0384 + 0x44),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x46),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x44),0);
      }
      FUN_0046d250(*(undefined4 *)(param_1 + 0x3a + local_6c * 4),local_98);
      FUN_0048477c(local_10,local_14,0x20,0x20,local_98,0xff,1);
    }
    local_68 = local_68 + 1;
    piVar5 = piVar5 + 1;
    piVar4 = piVar4 + 1;
    piVar3 = piVar3 + 4;
  } while (local_68 < 10);
  return;
}

