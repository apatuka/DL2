// FUN_00450c38 @ 00450c38 size=99 sig=undefined FUN_00450c38() cc=unknown
// callers: FUN_00450cb8
// callees: FUN_0046ca40

uint FUN_00450c38(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  
  uVar2 = DAT_0059f154;
  if ((5 < (int)DAT_0059f154) && (DAT_004ca3ac == 0)) {
    puVar3 = &DAT_005644f8;
    pcVar4 = &DAT_0059f161;
    for (iVar5 = 0; iVar5 < DAT_004d5aec; iVar5 = iVar5 + 1) {
      uVar2 = CONCAT31((int3)(uVar2 >> 8),*pcVar4);
      if (*pcVar4 != '\0') {
        uVar1 = FUN_0046ca40();
        uVar2 = uVar1 / 0x32;
        if (uVar1 % 0x32 == 0) {
          *puVar3 = 1;
          uVar2 = DAT_0059f154;
          puVar3[1] = DAT_0059f154;
        }
      }
      puVar3 = puVar3 + 2;
      pcVar4 = pcVar4 + 0x2d8;
    }
  }
  return uVar2;
}

