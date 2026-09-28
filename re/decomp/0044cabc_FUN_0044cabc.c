// FUN_0044cabc @ 0044cabc size=303 sig=undefined FUN_0044cabc() cc=unknown
// callers: FUN_0047bfdc,WinMain,FUN_0046147c
// callees: 

void FUN_0044cabc(void)

{
  int iVar1;
  char *pcVar2;
  
  DAT_005644f4 = (undefined2 *)0x0;
  iVar1 = 0;
  pcVar2 = &DAT_005f0414;
  do {
    if (*pcVar2 != '\0') {
      if (DAT_005644f4 == (undefined2 *)0x0) {
        pcVar2[0x11a] = '\0';
        pcVar2[0x11b] = '\0';
        pcVar2[0x11c] = '\0';
        pcVar2[0x11d] = '\0';
        pcVar2[0x116] = '\0';
        pcVar2[0x117] = '\0';
        pcVar2[0x118] = '\0';
        pcVar2[0x119] = '\0';
        DAT_005644f4 = &DAT_005f0410 + iVar1 * 0x91;
      }
      else {
        *(undefined2 **)(DAT_005644f4 + 0x8f) = &DAT_005f0410 + iVar1 * 0x91;
        *(undefined2 **)(pcVar2 + 0x116) = DAT_005644f4;
        pcVar2[0x11a] = '\0';
        pcVar2[0x11b] = '\0';
        pcVar2[0x11c] = '\0';
        pcVar2[0x11d] = '\0';
        DAT_005644f4 = &DAT_005f0410 + iVar1 * 0x91;
      }
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x122;
  } while (iVar1 < 0x4b0);
  pcVar2 = &DAT_005f0414;
  DAT_005644f0 = (undefined2 *)0x0;
  iVar1 = 0;
  do {
    if (*pcVar2 == '\0') {
      if (DAT_005644f0 == (undefined2 *)0x0) {
        pcVar2[0x11a] = '\0';
        pcVar2[0x11b] = '\0';
        pcVar2[0x11c] = '\0';
        pcVar2[0x11d] = '\0';
        pcVar2[0x116] = '\0';
        pcVar2[0x117] = '\0';
        pcVar2[0x118] = '\0';
        pcVar2[0x119] = '\0';
        DAT_005644f0 = &DAT_005f0410 + iVar1 * 0x91;
      }
      else {
        *(undefined2 **)(DAT_005644f0 + 0x8f) = &DAT_005f0410 + iVar1 * 0x91;
        *(undefined2 **)(pcVar2 + 0x116) = DAT_005644f0;
        pcVar2[0x11a] = '\0';
        pcVar2[0x11b] = '\0';
        pcVar2[0x11c] = '\0';
        pcVar2[0x11d] = '\0';
        DAT_005644f0 = &DAT_005f0410 + iVar1 * 0x91;
      }
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x122;
  } while (iVar1 < 0x4b0);
  return;
}

