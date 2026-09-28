// FUN_0042623c @ 0042623c size=834 sig=undefined FUN_0042623c() cc=unknown
// callers: FUN_00426594
// callees: FUN_00412f10,FUN_00412d38,FUN_00425ef8,FUN_004256f4,FUN_004258f8,free,FUN_004a2cb5,FUN_004257f0,FUN_00425ac4,FUN_0048db5d,FUN_0049eb44

undefined8 FUN_0042623c(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int local_c;
  
  if (((DAT_004b7cf8 != 0) && (*(char *)(DAT_004b7cf8 + 0x3c) == '\0')) && (DAT_004b7d00 == 0)) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    FUN_00412f10(DAT_004b7cf8);
    FUN_00412d38(DAT_004b7cf8,*(undefined4 *)(DAT_004b7ce4 + 0x3c));
    if (DAT_004b7cfc != 0) {
      free(DAT_004b7cfc);
      DAT_004b7cfc = 0;
    }
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00425ef8();
  iVar2 = FUN_004a2cb5(DAT_004b7ce4,&local_c);
  if (((iVar2 == 0) && (local_c != 0)) && (*(int *)(DAT_004b7ce4 + 100) == 0)) {
    switch(local_c) {
    case 5:
      iVar2 = local_c;
      goto LAB_0042658e;
    case 6:
      iVar2 = *(int *)(DAT_00557554 + 0x1a);
      if ((iVar2 == 0) || (*(int *)(iVar2 + 0x1a) == 0)) {
        if ((*(undefined **)(DAT_00557554 + 0x1a) != (undefined *)0x0) &&
           (*(undefined **)(DAT_00557554 + 0x1a) == &DAT_004d4d64)) {
          FUN_004258f8(&DAT_004d4d64,0);
          FUN_004256f4(&DAT_004d4d64);
          FUN_004257f0(&DAT_004d4d64);
          FUN_00425ac4(&DAT_004d4d64);
          DAT_00557554 = PTR_DAT_004d4d7a;
        }
      }
      else {
        FUN_004258f8(*(undefined4 *)(iVar2 + 0x1a),iVar2);
        FUN_004256f4(*(undefined4 *)(DAT_00557554 + 0x1a));
        FUN_004257f0(*(undefined4 *)(DAT_00557554 + 0x1a));
        FUN_00425ac4(*(undefined4 *)(DAT_00557554 + 0x1a));
        DAT_00557554 = *(undefined **)(DAT_00557554 + 0x1a);
      }
      break;
    case 7:
      iVar2 = FUN_0049eb44(DAT_004b7ce4,0xd,1,0x22,0,0);
      iVar3 = FUN_0049eb44(DAT_004b7ce4,0xd,1,0x18,0,0);
      if (iVar3 == iVar2) {
        DAT_00557554 = *(undefined **)(DAT_00557554 + 0x1a);
      }
      if (*(int *)(DAT_00557554 + 0x16) != 0) {
        FUN_004258f8(DAT_00557554,*(int *)(DAT_00557554 + 0x16));
        FUN_004257f0(*(undefined4 *)(DAT_00557554 + 0x16));
        FUN_004256f4(*(undefined4 *)(DAT_00557554 + 0x16));
        FUN_00425ac4(*(undefined4 *)(DAT_00557554 + 0x16));
        DAT_00557554 = *(undefined **)(DAT_00557554 + 0x16);
      }
      break;
    case 8:
      sVar1 = *(short *)(DAT_00557554 + 0x20);
      if (sVar1 < 1) {
        sVar1 = *(short *)(*(int *)(DAT_00557554 + 0x1a) + 0x1e);
      }
      iVar2 = (sVar1 + -1) * 0x24;
      FUN_004256f4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_004257f0(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_004258f8(*(int *)(DAT_00557554 + 0x1a),
                   *(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_00425ac4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      DAT_00557554 = (undefined *)(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      break;
    case 9:
      if ((int)*(short *)(DAT_00557554 + 0x20) <
          *(short *)(*(int *)(DAT_00557554 + 0x1a) + 0x1e) + -1) {
        iVar2 = *(short *)(DAT_00557554 + 0x20) + 1;
      }
      else {
        iVar2 = 0;
      }
      iVar2 = iVar2 * 0x24;
      FUN_004256f4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_004257f0(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_004258f8(*(int *)(DAT_00557554 + 0x1a),
                   *(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      FUN_00425ac4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
      DAT_00557554 = (undefined *)(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar2);
    }
  }
  iVar2 = 0;
LAB_0042658e:
  DAT_004d59a4 = 0;
  return CONCAT44(local_c,iVar2);
}

