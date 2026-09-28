// FUN_0045a3e4 @ 0045a3e4 size=294 sig=undefined FUN_0045a3e4() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: FUN_0046dc5c,BlitSprite8,FUN_00459ee0,FUN_0043ee40

void FUN_0045a3e4(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  if (DAT_004d59b0 == 0) {
    pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
    iVar3 = (int)pcVar1[1];
    iVar2 = *pcVar1 + 2;
    if (DAT_004d5ad0 == 0) {
      FUN_00459ee0(iVar2,iVar3,&local_8,&local_c);
      local_c = local_c + 0x10;
    }
    else {
      FUN_0043ee40(iVar2,iVar3,&local_8,&local_c);
      local_c = local_c + -0x10;
      local_8 = local_8 + -4;
    }
    iVar2 = FUN_0046dc5c(param_1);
    if (iVar2 != 0) {
      BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x58),
                  *(short *)(PTR_DAT_004d0384 + 0x50) + local_8,
                  *(short *)(PTR_DAT_004d0384 + 0x52) + local_c,
                  (int)*(short *)(PTR_DAT_004d0384 + 0x54),(int)*(short *)(PTR_DAT_004d0384 + 0x56),
                  (int)*(short *)(PTR_DAT_004d0384 + 0x54),0);
    }
    if (DAT_004d5ad0 == 0) {
      local_c = local_c + 0x10;
    }
    else {
      local_c = local_c + -0x10;
      local_8 = local_8 + -4;
    }
    if (((1 << ((byte)DAT_0058f1f4 & 0x1f) & *(uint *)(param_1 + 0x8a8)) != 0) ||
       ((*(int *)(param_1 + 0x8a8) != 0 && ((DAT_00583c20 != 0 || (DAT_004d5aa0 != '\0')))))) {
      BlitSprite8(*(undefined4 *)(PTR_DAT_004d0384 + 0x68),
                  *(short *)(PTR_DAT_004d0384 + 0x60) + local_8,
                  *(short *)(PTR_DAT_004d0384 + 0x62) + local_c,
                  (int)*(short *)(PTR_DAT_004d0384 + 100),(int)*(short *)(PTR_DAT_004d0384 + 0x66),
                  (int)*(short *)(PTR_DAT_004d0384 + 100),0);
    }
  }
  return;
}

