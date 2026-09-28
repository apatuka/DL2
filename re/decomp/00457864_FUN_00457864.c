// FUN_00457864 @ 00457864 size=223 sig=undefined FUN_00457864() cc=unknown
// callers: InitCYGame,GetNetGameOptions
// callees: SetErrorMode,GetDriveTypeA,FindFirstFileA,FindClose,GetLogicalDrives
// strings: \".\\\\\\\\DEADLOCK.TXT\"|\".\\\\\\\\DEADCINE.CAM\"

UINT FUN_00457864(void)

{
  char cVar1;
  DWORD DVar2;
  UINT UVar3;
  HANDLE hFindFile;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  _WIN32_FIND_DATAA _Stack_150;
  
  SetErrorMode(1);
  DVar2 = GetLogicalDrives();
  UVar3 = 0x43;
  if ((DVar2 != 0) && (UVar3 = GetDriveTypeA(&DAT_004d02e0), UVar3 == 3)) {
    s____DEADLOCK_TXT_004d02d0[0] = DAT_004d02e0;
    s____DEADCINE_CAM_004d02c0[0] = DAT_004d02e0;
    hFindFile = FindFirstFileA(s____DEADCINE_CAM_004d02c0,&_Stack_150);
    if (hFindFile == (HANDLE)0xffffffff) {
      DAT_004d5980 = 0;
    }
    else {
      DAT_004d5980 = 1;
      FindClose(hFindFile);
      uVar4 = 0xffffffff;
      pcVar6 = &DAT_004d02e0;
      do {
        pcVar7 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar6 = pcVar7 + -uVar4;
      pcVar7 = &DAT_0058f20c;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
      DAT_004d59ac = 1;
    }
    UVar3 = 1;
  }
  return UVar3;
}

