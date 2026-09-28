// FUN_0045a50c @ 0045a50c size=472 sig=undefined FUN_0045a50c() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: FUN_0044d1e4,BlitSprite8,FUN_00459ee0,FUN_0043ee40

void FUN_0045a50c(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  if ((DAT_004d59b0 == 0) && ('\x01' < *(char *)(param_1 + 0x66 + DAT_0058f1f4))) {
    pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
    iVar3 = (int)pcVar1[1];
    iVar2 = *pcVar1 + -1;
    if (DAT_004d5ad0 == 0) {
      FUN_00459ee0(iVar2,iVar3,&local_8,&local_c);
      local_c = local_c + 0x10;
    }
    else {
      FUN_0043ee40(iVar2,iVar3,&local_8,&local_c);
      local_c = local_c + -0x10;
      local_8 = local_8 + -4;
    }
    if ((((DAT_004c5458 <= local_8) && (local_8 < DAT_004c5458 + DAT_004c5460)) &&
        (DAT_004c545c <= local_c)) && (local_c < DAT_004c545c + DAT_004c5464)) {
      iVar2 = FUN_0044d1e4(param_1,7,0);
      if (iVar2 != -1) {
        BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 8),*(short *)PTR_DAT_004d0384 + local_8,
                    *(short *)(PTR_DAT_004d0384 + 2) + local_c,(int)*(short *)(PTR_DAT_004d0384 + 4)
                    ,(int)*(short *)(PTR_DAT_004d0384 + 6),(int)*(short *)(PTR_DAT_004d0384 + 4),0);
      }
      iVar2 = FUN_0044d1e4(param_1,8,0);
      if (iVar2 != -1) {
        BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x18),
                    *(short *)(PTR_DAT_004d0384 + 0x10) + local_8 + 0x10,
                    *(short *)(PTR_DAT_004d0384 + 0x12) + local_c,
                    (int)*(short *)(PTR_DAT_004d0384 + 0x14),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x16),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x14),0);
      }
      iVar2 = FUN_0044d1e4(param_1,0xc,0);
      if (iVar2 != -1) {
        BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x28),
                    *(short *)(PTR_DAT_004d0384 + 0x20) + local_8,
                    *(short *)(PTR_DAT_004d0384 + 0x22) + local_c + 0x10,
                    (int)*(short *)(PTR_DAT_004d0384 + 0x24),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x26),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x24),0);
      }
      if (((DAT_004d5aa0 == '\0') && (*(char *)(param_1 + 0x20) != -1)) &&
         (*(char *)(param_1 + 0x35) < 'd')) {
        BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x38),
                    *(short *)(PTR_DAT_004d0384 + 0x30) + local_8 + 0x10,
                    *(short *)(PTR_DAT_004d0384 + 0x32) + local_c + 0x10,
                    (int)*(short *)(PTR_DAT_004d0384 + 0x34),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x36),
                    (int)*(short *)(PTR_DAT_004d0384 + 0x34),0);
      }
    }
  }
  return;
}

