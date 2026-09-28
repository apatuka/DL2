// FUN_0043aa88 @ 0043aa88 size=453 sig=undefined FUN_0043aa88() cc=unknown
// callers: RunAITurns,WinMain
// callees: FUN_0049eb44,FUN_004a19b4

void FUN_0043aa88(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  
  if (DAT_004d5aa0 == '\0') {
    FUN_0049eb44(DAT_004c48a0,0x26,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x27,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x28,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x29,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2a,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2b,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2c,1,0x3c,0,1);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,0x27,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x28,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x29,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2a,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2b,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2c,1,0x3c,0,1);
    FUN_0049eb44(DAT_004c48a0,0x2d,1,0x3c,0,1);
  }
  if ((DAT_0058f1ec == 0) && (DAT_004d5a50 != 0)) {
    pcVar4 = &DAT_0059f161;
    for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
      if (*pcVar4 != '\0') {
        cVar2 = pcVar4[1];
        iVar1 = iVar3 + 0x26;
        FUN_0049eb44(DAT_004c48a0,iVar1,1,0x3c,1,1);
        FUN_0049eb44(DAT_004c48a0,iVar1,1,0xb,0,0);
        FUN_004a19b4(DAT_004c48a0,iVar1,1,0xd,cVar2 + 0xfa1);
      }
      pcVar4 = pcVar4 + 0x2d8;
    }
  }
  return;
}

