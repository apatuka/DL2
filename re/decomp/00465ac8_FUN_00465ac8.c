// FUN_00465ac8 @ 00465ac8 size=211 sig=undefined FUN_00465ac8() cc=unknown
// callers: FUN_00465df8
// callees: DebugMessage,LoadPhaseSprites,memset
// strings: \"Could not load Control Phase sprites.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00465ac8(void)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar6 = 0;
  memset(&DAT_0058df4c,0,0x6ac);
  memset(&DAT_0058e5f8,0,0x6ac);
  pcVar1 = &DAT_0059f162;
  for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
    iVar4 = (int)*pcVar1;
    pcVar1 = pcVar1 + 0x2d8;
    *(undefined4 *)(&DAT_0058e158 + iVar4 * 4) = 1;
    *(undefined4 *)(&DAT_0058e174 + iVar4 * 4) = 1;
    *(undefined4 *)(&DAT_0058e1c8 + iVar4 * 4) = 1;
    *(undefined4 *)(&DAT_0058e1e4 + iVar4 * 4) = 1;
    *(undefined4 *)(&DAT_0058e190 + iVar4 * 4) = 1;
    *(undefined4 *)(&DAT_0058e1ac + iVar4 * 4) = 1;
  }
  _DAT_0058df78 = 1;
  iVar3 = 0;
  piVar5 = &DAT_0058e5f8;
  piVar2 = &DAT_0058df4c;
  do {
    if (*piVar2 != 0) {
      *piVar5 = iVar3;
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x1ab);
  iVar3 = LoadPhaseSprites(&DAT_0058e5f8,iVar6);
  if (iVar3 == 0) {
    DebugMessage(s_Could_not_load_Control_Phase_spr_004d4e8d);
  }
  return;
}

