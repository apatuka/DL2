// FUN_00449718 @ 00449718 size=70 sig=undefined FUN_00449718() cc=unknown
// callers: FUN_0045e554
// callees: 

uint FUN_00449718(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  
  uVar3 = 0;
  if ((DAT_0058f1ec == 0) && (DAT_004d5a50 != 0)) {
    pcVar2 = &DAT_0059f168;
    for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
      if (*pcVar2 == '\0') {
        uVar3 = uVar3 | 1 << ((byte)iVar1 & 0x1f);
      }
      pcVar2 = pcVar2 + 0x2d8;
    }
  }
  return uVar3;
}

