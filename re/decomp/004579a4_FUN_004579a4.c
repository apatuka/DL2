// FUN_004579a4 @ 004579a4 size=177 sig=undefined FUN_004579a4() cc=unknown
// callers: WinMain
// callees: FindFirstFileA,FindClose
// strings: \".\\\\\\\\DEADCINE.CAM\"

void FUN_004579a4(void)

{
  char *pcVar1;
  bool bVar2;
  HANDLE hFindFile;
  int iVar3;
  char *pcVar4;
  char local_15c [16];
  _WIN32_FIND_DATAA local_14c;
  
  pcVar4 = s____DEADCINE_CAM_004d02e4;
  pcVar1 = local_15c;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pcVar1 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar1 = (char *)((int)pcVar1 + 4);
  }
  bVar2 = false;
  if (((DAT_004d02bc == 0) &&
      (((DAT_004d59ac != 0 || (DAT_0058f20c != '\0')) && ((code *)PTR_FUN_004d02b8 != FUN_00457a58))
      )) && (DAT_004d59c4 == 0)) {
    while( true ) {
      local_15c[0] = DAT_0058f20c;
      hFindFile = FindFirstFileA(local_15c,&local_14c);
      if (hFindFile != (HANDLE)0xffffffff) break;
      if (bVar2) {
        DAT_004d02bc = 1;
        DAT_004d59ac = 0;
        DAT_0058f20c = 0;
        return;
      }
      bVar2 = true;
    }
    FindClose(hFindFile);
  }
  DAT_004d02bc = 1;
  return;
}

