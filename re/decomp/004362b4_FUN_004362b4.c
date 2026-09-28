// FUN_004362b4 @ 004362b4 size=117 sig=undefined FUN_004362b4() cc=unknown
// callers: FUN_0043632c
// callees: FUN_0049eb44,FUN_004a4025,FUN_004691f8,FUN_004493dc
// strings: \"New Player\"

void FUN_004362b4(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char acStack_28 [32];
  
  iVar2 = FUN_0049eb44(DAT_004c465c,3,1,0xe,0x20,acStack_28);
  if (iVar2 != 0) {
    uVar3 = 0xffffffff;
    pcVar5 = acStack_28;
    do {
      pcVar6 = pcVar5;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = s_New_Player_00509804;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  FUN_004a4025(DAT_004c465c);
  DAT_004c465c = 0;
  DAT_004d59b4 = DAT_00558eac;
  FUN_004493dc(0);
  FUN_004691f8();
  return;
}

