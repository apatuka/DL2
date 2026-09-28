// FUN_00444e88 @ 00444e88 size=152 sig=undefined FUN_00444e88() cc=unknown
// callers: FUN_00480d78,FUN_0048149c
// callees: memset,FUN_00444fd4

void FUN_00444e88(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = DAT_00561a30;
  while (iVar3 != 0) {
    iVar1 = *(int *)(iVar3 + 0x38);
    FUN_00444fd4(iVar3);
    iVar3 = iVar1;
  }
  memset(&DAT_00561a34,0,0x2580);
  iVar3 = 0;
  puVar2 = &DAT_00561a34;
  do {
    if (iVar3 == 0x95) {
      *(undefined4 *)(puVar2 + 0x38) = 0;
    }
    else {
      *(undefined **)(puVar2 + 0x38) = &DAT_00561a74 + iVar3 * 0x40;
    }
    if (iVar3 == 0) {
      *(undefined4 *)(puVar2 + 0x3c) = 0;
    }
    else {
      *(undefined **)(puVar2 + 0x3c) = &DAT_005619f4 + iVar3 * 0x40;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 0x40;
  } while (iVar3 < 0x96);
  DAT_00561a30 = 0;
  DAT_00563fb4 = 0;
  DAT_00563fb8 = &DAT_00561a34;
  DAT_004c50a8 = 0;
  return;
}

