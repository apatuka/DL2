// FUN_00449760 @ 00449760 size=74 sig=undefined FUN_00449760() cc=unknown
// callers: FUN_00474f5c,RunAITurns,FUN_0043acd4,FUN_00476fb8,FUN_00476ffc,FUN_0044a000
// callees: FUN_0043ac50

void FUN_00449760(void)

{
  int iVar1;
  char *pcVar2;
  
  if ((DAT_0058f1ec == 0) && (DAT_004d5a50 != 0)) {
    pcVar2 = &DAT_0059f168;
    for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
      if (*pcVar2 == '\x01') {
        FUN_0043ac50(1,iVar1);
      }
      else {
        FUN_0043ac50(0,iVar1);
      }
      pcVar2 = pcVar2 + 0x2d8;
    }
  }
  return;
}

