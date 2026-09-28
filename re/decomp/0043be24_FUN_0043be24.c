// FUN_0043be24 @ 0043be24 size=114 sig=undefined FUN_0043be24() cc=unknown
// callers: FUN_0043be98,FUN_0047361c
// callees: FUN_0043afe8,FUN_00416af0,FUN_00472fb4,FUN_004748dc,FUN_00449dec

void FUN_0043be24(void)

{
  int iVar1;
  char *pcVar2;
  byte bVar3;
  int iVar4;
  
  iVar1 = FUN_004748dc();
  if (iVar1 == 0) {
    bVar3 = 0;
    iVar1 = 0;
    pcVar2 = &DAT_0059f161;
    do {
      if (*pcVar2 != '\0') {
        bVar3 = bVar3 | '\x01' << (pcVar2[1] & 0x1fU);
      }
      iVar1 = iVar1 + 1;
      pcVar2 = pcVar2 + 0x2d8;
    } while (iVar1 < 7);
    DAT_00559d9c = 0;
    iVar1 = FUN_00416af0(bVar3);
    iVar4 = 0;
    pcVar2 = &DAT_0059f161;
    do {
      if ((*pcVar2 != '\0') && (iVar1 == pcVar2[1])) {
        FUN_00472fb4(iVar4);
      }
      iVar4 = iVar4 + 1;
      pcVar2 = pcVar2 + 0x2d8;
    } while (iVar4 < 7);
    FUN_0043afe8();
    FUN_00449dec();
  }
  return;
}

