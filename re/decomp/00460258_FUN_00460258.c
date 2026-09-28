// FUN_00460258 @ 00460258 size=215 sig=undefined FUN_00460258() cc=unknown
// callers: ChCht
// callees: memcpy,WriteFile

undefined4 FUN_00460258(HANDLE param_1)

{
  char *pcVar1;
  BOOL BVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_130 [282];
  ushort *local_16;
  ushort *local_12;
  DWORD local_c;
  int local_8;
  
  iVar4 = 0;
  local_8 = 0;
  pcVar1 = &DAT_005f0414;
  do {
    if (*pcVar1 != '\0') {
      local_8 = local_8 + 1;
    }
    iVar4 = iVar4 + 1;
    pcVar1 = pcVar1 + 0x122;
  } while (iVar4 < 0x4b0);
  BVar2 = WriteFile(param_1,&local_8,4,&local_c,(LPOVERLAPPED)0x0);
  if (BVar2 == 0) {
    uVar3 = 0;
  }
  else {
    iVar4 = 0;
    pcVar1 = &DAT_005f0414;
    do {
      if (*pcVar1 != '\0') {
        memcpy(local_130,&DAT_005f0410 + iVar4 * 0x91,0x122);
        if (local_16 != (ushort *)0x0) {
          local_16 = (ushort *)(uint)*local_16;
        }
        if (local_12 != (ushort *)0x0) {
          local_12 = (ushort *)(uint)*local_12;
        }
        BVar2 = WriteFile(param_1,local_130,0x122,&local_c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          return 0;
        }
      }
      iVar4 = iVar4 + 1;
      pcVar1 = pcVar1 + 0x122;
    } while (iVar4 < 0x4b0);
    uVar3 = 1;
  }
  return uVar3;
}

