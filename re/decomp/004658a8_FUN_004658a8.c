// FUN_004658a8 @ 004658a8 size=515 sig=undefined FUN_004658a8() cc=unknown
// callers: FUN_00465df8,WinMain
// callees: DebugMessage,LoadPhaseSprites,memset
// strings: \"Could not load Settlement Phase sprites.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004658a8(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  int *piVar6;
  short *psVar7;
  int local_14;
  
  local_14 = 0;
  memset(&DAT_0058df4c,0,0x6ac);
  memset(&DAT_0058e5f8,0,0x6ac);
  switch(DAT_004d5b1c) {
  case 0:
    _DAT_0058e12c = 1;
    _DAT_0058e130 = 1;
    break;
  case 1:
    _DAT_0058e144 = 1;
    _DAT_0058e148 = 1;
    break;
  case 2:
    _DAT_0058e13c = 1;
    _DAT_0058e140 = 1;
    break;
  case 3:
    _DAT_0058e134 = 1;
    _DAT_0058e138 = 1;
    break;
  case 4:
    _DAT_0058e124 = 1;
    _DAT_0058e128 = 1;
    break;
  case 5:
    _DAT_0058e14c = 1;
    _DAT_0058e150 = 1;
    break;
  case 6:
    _DAT_0058e11c = 1;
    _DAT_0058e120 = 1;
  }
  iVar2 = 0;
  piVar4 = &DAT_004d4e14;
  do {
    iVar3 = *piVar4;
    piVar4 = piVar4 + 1;
    iVar2 = iVar2 + 1;
    (&DAT_0058df4c)[iVar3] = 1;
  } while (iVar2 < 0xe);
  iVar2 = 0;
  psVar7 = &DAT_004f9dc0;
  do {
    if ((((iVar2 == 1) || (iVar2 == 2)) || (iVar2 == 3)) ||
       (((iVar2 == 0x27 || (iVar2 == 0x25)) || (iVar2 == 0x17)))) {
      pcVar5 = &DAT_0059f162;
      for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 0x2d8;
        (&DAT_0058df4c)[(int)*psVar7 + (int)cVar1] = 1;
      }
    }
    else {
      (&DAT_0058df4c)[*psVar7] = 1;
    }
    iVar2 = iVar2 + 1;
    psVar7 = psVar7 + 0x19;
  } while (iVar2 < 0x30);
  pcVar5 = &DAT_0059f162;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    iVar3 = (int)*pcVar5;
    pcVar5 = pcVar5 + 0x2d8;
    *(undefined4 *)(&DAT_0058e1c8 + iVar3 * 4) = 1;
    *(undefined4 *)(&DAT_0058e1e4 + iVar3 * 4) = 1;
    *(undefined4 *)(&DAT_0058e190 + iVar3 * 4) = 1;
    *(undefined4 *)(&DAT_0058e1ac + iVar3 * 4) = 1;
  }
  iVar2 = 0;
  piVar4 = &DAT_0058e5f8;
  piVar6 = &DAT_0058df4c;
  do {
    if (*piVar6 != 0) {
      *piVar4 = iVar2;
      local_14 = local_14 + 1;
      piVar4 = piVar4 + 1;
    }
    iVar2 = iVar2 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar2 < 0x1ab);
  iVar2 = LoadPhaseSprites(&DAT_0058e5f8,local_14);
  if (iVar2 == 0) {
    DebugMessage(s_Could_not_load_Settlement_Phase_s_004d4e64);
  }
  return;
}

