// FUN_004605e0 @ 004605e0 size=273 sig=undefined FUN_004605e0() cc=unknown
// callers: ChCht
// callees: WriteFile,memcpy

undefined4 FUN_004605e0(HANDLE param_1)

{
  char *pcVar1;
  BOOL BVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  undefined1 local_68 [56];
  int local_30;
  int local_2c;
  int local_28;
  uint local_20 [3];
  ushort *local_14;
  ushort *local_10;
  DWORD local_c;
  int local_8;
  
  local_8 = 0;
  pcVar1 = &DAT_00645376;
  iVar6 = 0;
  do {
    if (*pcVar1 != '\0') {
      local_8 = local_8 + 1;
    }
    iVar6 = iVar6 + 1;
    pcVar1 = pcVar1 + 0x5c;
  } while (iVar6 < 0x230);
  BVar2 = WriteFile(param_1,&local_8,4,&local_c,(LPOVERLAPPED)0x0);
  if (BVar2 == 0) {
    uVar3 = 0;
  }
  else {
    iVar6 = 0;
    pcVar1 = &DAT_00645376;
    do {
      if (*pcVar1 != '\0') {
        memcpy(local_68,&DAT_00645370 + iVar6 * 0x2e,0x5c);
        if (local_30 != 0) {
          local_30 = (int)*(short *)(local_30 + 0x1a);
        }
        if (local_2c != 0) {
          local_2c = (int)*(short *)(local_2c + 0x1a);
        }
        if (local_28 != 0) {
          local_28 = (int)*(short *)(local_28 + 0x1a);
        }
        if (local_14 != (ushort *)0x0) {
          local_14 = (ushort *)(uint)*local_14;
        }
        if (local_10 != (ushort *)0x0) {
          local_10 = (ushort *)(uint)*local_10;
        }
        iVar5 = 0;
        puVar4 = local_20;
        do {
          if ((ushort *)*puVar4 != (ushort *)0x0) {
            *puVar4 = (uint)*(ushort *)*puVar4;
          }
          iVar5 = iVar5 + 1;
          puVar4 = puVar4 + 1;
        } while (iVar5 < 3);
        BVar2 = WriteFile(param_1,local_68,0x5c,&local_c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          return 0;
        }
      }
      iVar6 = iVar6 + 1;
      pcVar1 = pcVar1 + 0x5c;
    } while (iVar6 < 0x230);
    uVar3 = 1;
  }
  return uVar3;
}

