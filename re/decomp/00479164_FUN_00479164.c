// FUN_00479164 @ 00479164 size=447 sig=undefined FUN_00479164() cc=unknown
// callers: ResetNetGame
// callees: memset,memcpy

void FUN_00479164(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *local_2e8;
  undefined1 local_2e4 [728];
  
  memset(&DAT_0065405c,0,0xc4);
  memset(&DAT_00654120,0,0xc4);
  iVar3 = 0;
  piVar4 = &DAT_0065361c;
  pcVar1 = &DAT_0059f161;
  do {
    if (*pcVar1 == '\0') {
      *piVar4 = -1;
    }
    else {
      *piVar4 = (int)pcVar1[1];
      memcpy(&DAT_0065405c + iVar3 * 7,&DAT_0059f3da + iVar3 * 0xb6,0x1c);
      memcpy(&DAT_00654120 + iVar3 * 7,&DAT_0059f3f6 + iVar3 * 0xb6,0x1c);
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar3 < 7);
  iVar3 = 0;
  local_2e8 = &DAT_0059f162;
  piVar4 = &DAT_00653600;
  do {
    if ((*piVar4 != -1) && (*piVar4 != (int)*local_2e8)) {
      iVar2 = 0;
      pcVar1 = &DAT_0059f162;
      do {
        if ((int)*pcVar1 == *piVar4) {
          memcpy(local_2e4,&DAT_0059f160 + iVar3 * 0x2d8,0x2d8);
          memcpy(&DAT_0059f160 + iVar3 * 0x2d8,&DAT_0059f160 + iVar2 * 0x2d8,0x2d8);
          memcpy(&DAT_0059f160 + iVar2 * 0x2d8,local_2e4,0x2d8);
          break;
        }
        iVar2 = iVar2 + 1;
        pcVar1 = pcVar1 + 0x2d8;
      } while (iVar2 < 7);
    }
    iVar3 = iVar3 + 1;
    local_2e8 = local_2e8 + 0x2d8;
    piVar4 = piVar4 + 1;
    if (6 < iVar3) {
      return;
    }
  } while( true );
}

