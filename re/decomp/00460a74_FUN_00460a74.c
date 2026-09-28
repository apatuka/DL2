// FUN_00460a74 @ 00460a74 size=783 sig=undefined FUN_00460a74() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile,FUN_004b02a8,FUN_0044da3c,FUN_004750c4,memset,FUN_00484c2c,FUN_004609e8,FUN_0047510c

/* WARNING: Removing unreachable block (ram,0x00460aba) */

undefined4 FUN_00460a74(HANDLE param_1)

{
  undefined2 uVar1;
  BOOL BVar2;
  int iVar3;
  undefined4 uVar4;
  uint *puVar5;
  undefined4 *puVar6;
  DWORD local_8;
  
  memset(&DAT_005a43d0,0,0x4c040);
  puVar6 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar6) {
      if ((DAT_00583da4 == 0) || (DAT_00583da4 == 1)) {
        for (puVar6 = &DAT_005a4eac; puVar6 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
            puVar6 = puVar6 + 0x2b7) {
          uVar1 = FUN_0044da3c(puVar6);
          *(undefined2 *)(puVar6 + 0x26c) = uVar1;
        }
      }
      for (puVar6 = (undefined4 *)&DAT_00645370;
          (puVar6 < &DAT_00651cb0 && (*(char *)((int)puVar6 + 6) != '\0')); puVar6 = puVar6 + 0x17)
      {
        if (puVar6[0xe] != 0) {
          puVar6[0xe] = &DAT_005a43d0 + puVar6[0xe] * 0xadc;
        }
        if (puVar6[0xf] != 0) {
          puVar6[0xf] = &DAT_005a43d0 + puVar6[0xf] * 0xadc;
        }
        if (puVar6[0x10] != 0) {
          puVar6[0x10] = &DAT_005a43d0 + puVar6[0x10] * 0xadc;
        }
      }
      return 1;
    }
    if ((DAT_00583da4 == 0) || (DAT_00583da4 == 1)) {
      BVar2 = ReadFile(param_1,puVar6,0xac4 - DAT_004d1cf8,&local_8,(LPOVERLAPPED)0x0);
      if (BVar2 == 0) {
        return 0;
      }
      iVar3 = FUN_004b02a8(8);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_00484c2c(iVar3);
      }
      *(undefined4 *)((int)puVar6 + 0x99a) = uVar4;
      iVar3 = FUN_004b02a8(8);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_00484c2c(iVar3);
      }
      *(undefined4 *)((int)puVar6 + 0x99e) = uVar4;
      iVar3 = FUN_004b02a8(8);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_00484c2c(iVar3);
      }
      *(undefined4 *)((int)puVar6 + 0x9a2) = uVar4;
      iVar3 = FUN_004b02a8(8);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_00484c2c(iVar3);
      }
      *(undefined4 *)((int)puVar6 + 0x9a6) = uVar4;
      iVar3 = FUN_004b02a8(8);
      if (iVar3 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_00484c2c(iVar3);
      }
      *(undefined4 *)((int)puVar6 + 0x9aa) = uVar4;
      *(undefined1 *)((int)puVar6 + 0x9ae) = 0;
    }
    else {
      BVar2 = ReadFile(param_1,puVar6,0xadc - DAT_004d1cf8,&local_8,(LPOVERLAPPED)0x0);
      if (BVar2 == 0) {
        return 0;
      }
      iVar3 = FUN_004609e8(param_1,(undefined *)((int)puVar6 + 0x99a));
      if ((((iVar3 == 0) ||
           (iVar3 = FUN_004609e8(param_1,(undefined *)((int)puVar6 + 0x99e)), iVar3 == 0)) ||
          (iVar3 = FUN_004609e8(param_1,(undefined *)((int)puVar6 + 0x9a2)), iVar3 == 0)) ||
         ((iVar3 = FUN_004609e8(param_1,(undefined *)((int)puVar6 + 0x9a6)), iVar3 == 0 ||
          (iVar3 = FUN_004609e8(param_1,(undefined *)((int)puVar6 + 0x9aa)), iVar3 == 0)))) {
        return 0;
      }
    }
    if (*(int *)((int)puVar6 + 0x76) != 0) {
      uVar4 = FUN_0047510c(*(undefined4 *)((int)puVar6 + 0x76));
      *(undefined4 *)((int)puVar6 + 0x76) = uVar4;
    }
    if (*(int *)((int)puVar6 + 0x7a) != 0) {
      uVar4 = FUN_0047510c(*(undefined4 *)((int)puVar6 + 0x7a));
      *(undefined4 *)((int)puVar6 + 0x7a) = uVar4;
    }
    puVar5 = puVar6 + 0x20;
    for (iVar3 = 0; iVar3 < *(char *)((int)puVar6 + 0x7e); iVar3 = iVar3 + 1) {
      *puVar5 = (uint)(&DAT_005a0550 + (*puVar5 >> 0x10) * 400 + (uint)(ushort)*puVar5 * 10);
      puVar5 = puVar5 + 1;
    }
    iVar3 = 0;
    do {
      if (puVar6[iVar3 * 0xd + 0x55] != 0) {
        uVar4 = FUN_004750c4(puVar6[iVar3 * 0xd + 0x55]);
        puVar6[iVar3 * 0xd + 0x55] = uVar4;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x24);
    puVar6 = puVar6 + 0x2b7;
  } while( true );
}

