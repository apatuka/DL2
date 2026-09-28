// FUN_00442184 @ 00442184 size=309 sig=undefined FUN_00442184() cc=unknown
// callers: FUN_004437c4
// callees: memset,FUN_00441fa4,FUN_0046ab18

void FUN_00442184(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  short *psVar4;
  undefined2 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 local_80 [76];
  short local_34 [22];
  int *local_8;
  
  iVar7 = 0;
  puVar5 = &DAT_0055dc62;
  do {
    memset(&DAT_0055dc60 + iVar7 * 0x3d,0,0x7a);
    *puVar5 = (short)iVar7;
    iVar7 = iVar7 + 1;
    puVar5[-1] = 0xffff;
    puVar5[1] = 0xffff;
    puVar5 = puVar5 + 0x3d;
  } while (iVar7 < 0x20);
  for (puVar6 = &DAT_005a4eac; puVar6 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar6 = puVar6 + 0x2b7) {
    iVar7 = (int)*(char *)(puVar6 + 0x26d);
    if (iVar7 != -1) {
      iVar2 = iVar7 * 0x7a;
      (&DAT_0055dc60)[iVar7 * 0x3d] = (short)*(char *)((int)puVar6 + 0x22);
      (&DAT_0055dc64)[iVar7 * 0x3d] = (short)*(char *)(puVar6 + 8);
      *(short *)(&DAT_0055dc66 + iVar2) = *(short *)(&DAT_0055dc66 + iVar2) + 1;
      *(short *)(&DAT_0055dc96 + iVar2) =
           *(short *)(&DAT_0055dc96 + iVar2) + *(short *)(puVar6 + 0xc);
      psVar3 = (short *)((int)&DAT_0055dc68 + *(char *)((int)puVar6 + 0x21) * 2 + iVar2);
      *psVar3 = *psVar3 + 1;
      iVar7 = 0;
      local_8 = puVar6 + 0x55;
      do {
        iVar1 = *local_8;
        if (iVar1 != 0) {
          *(short *)(&DAT_0055dc94 + iVar2) = *(short *)(&DAT_0055dc94 + iVar2) + 1;
          psVar3 = (short *)(iVar2 + 0x55dc98 +
                            (char)(&DAT_004f9dc3)[*(char *)(iVar1 + 4) * 0x32] * 2);
          *psVar3 = *psVar3 + 1;
        }
        iVar7 = iVar7 + 1;
        local_8 = local_8 + 0xd;
      } while (iVar7 < 0x24);
      memset(local_80,0,0x78);
      FUN_0046ab18(puVar6,local_80);
      iVar7 = 0;
      psVar3 = (short *)(&DAT_0055dcc2 + iVar2);
      psVar4 = local_34;
      do {
        *psVar3 = *psVar3 + *psVar4;
        iVar7 = iVar7 + 1;
        psVar3 = psVar3 + 1;
        psVar4 = psVar4 + 2;
      } while (iVar7 < 0xb);
    }
  }
  FUN_00441fa4(param_1);
  return;
}

