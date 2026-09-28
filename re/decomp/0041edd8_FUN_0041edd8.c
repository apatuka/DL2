// FUN_0041edd8 @ 0041edd8 size=585 sig=undefined FUN_0041edd8() cc=unknown
// callers: FUN_0041f544
// callees: FUN_004503f4,FUN_0048db5d,FUN_0041e9e8,FUN_0041ecc8,free,FUN_0049eb44,FUN_00412f10,FUN_00412d38,FUN_0041edac,MessagePump,FUN_0046ca40,FUN_0041f354,FUN_0044a000,FUN_00450508,FUN_0045093c

void FUN_0041edd8(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  uint uVar5;
  uint local_210;
  undefined1 local_20c [512];
  
  iVar1 = FUN_0049eb44(DAT_004b7974,0x1e,1,0x22,0,0);
  iVar2 = FUN_0049eb44(DAT_004b7974,0x1e,1,0x18,0,0);
  if (iVar1 < iVar2) {
    FUN_0049eb44(DAT_004b7974,0x1e,1,0x37,iVar1,&local_210);
    uVar3 = FUN_004503f4((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],DAT_0053b8a8,local_210);
  }
  else {
    uVar5 = FUN_00450508((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],DAT_0053b8a8);
    local_210 = FUN_0046ca40(uVar5);
    local_210 = local_210 % uVar5;
    uVar3 = FUN_004503f4((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],DAT_0053b8a8,local_210);
  }
  FUN_0049eb44(DAT_004b7974,0x1d,1,0xe,0x1ff,local_20c);
  if (DAT_0053b8a8 == 0x24) {
    iVar1 = FUN_0041e9e8(uVar3,local_20c);
  }
  else {
    iVar1 = FUN_0041e9e8(uVar3,0);
  }
  if (iVar1 != 0) {
    FUN_0041f354();
    FUN_0044a000();
    DAT_004d59a4 = 1;
    FUN_0048db5d(0);
    DAT_004d59a4 = 0;
    FUN_0041ecc8();
    if ((DAT_004b7988 != 0) && (DAT_004b7990 == 0)) {
      while (*(char *)(DAT_004b7988 + 0x3c) != '\0') {
        MessagePump();
      }
      DAT_004c5b78 = 0;
      DAT_004c5b70 = 0;
      DAT_004c5b7c = 0;
      DAT_004c5b74 = 0;
      FUN_00412f10(DAT_004b7988);
      FUN_00412d38(DAT_004b7988,*(undefined4 *)(DAT_004b7974 + 0x3c));
      if (DAT_004b798c != 0) {
        free(DAT_004b798c);
        DAT_004b798c = 0;
      }
    }
  }
  uVar5 = 0;
  iVar1 = 0;
  piVar4 = &DAT_0053b88c;
  do {
    if ((*piVar4 != 0) && (iVar2 = FUN_0041edac(iVar1), iVar2 != -1)) {
      uVar5 = uVar5 | 1 << ((byte)iVar2 & 0x1f);
    }
    iVar1 = iVar1 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar1 < 7);
  if (DAT_0053b8a8 == 0x24) {
    FUN_0045093c(DAT_0058f1f4,uVar5,0xfffffffe,local_20c,0,0,0);
  }
  else {
    FUN_0045093c(DAT_0058f1f4,uVar5,DAT_0053b8a8,local_210,0,0,0);
  }
  return;
}

