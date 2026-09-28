// FUN_0042dbb8 @ 0042dbb8 size=220 sig=undefined FUN_0042dbb8() cc=unknown
// callers: FUN_0042e080
// callees: Sleep,SelRace,FUN_004a26e8,FUN_0042da3c

void FUN_0042dbb8(void)

{
  int *piVar1;
  int iVar2;
  
  if (DAT_00557c80 == 0) {
    if (DAT_004c36ac != 0) {
      FUN_004a26e8(DAT_004c36ac);
    }
    if (((&DAT_0059f161)[DAT_00557c7c * 0x2d8] == '\0') ||
       ('\x02' < (char)(&DAT_0059f161)[DAT_00557c7c * 0x2d8])) {
      DAT_004c366c = SelRace();
      (&DAT_0059f162)[DAT_00557c7c * 0x2d8] = (undefined1)DAT_004c366c;
      FUN_0042da3c();
      Sleep(1000);
      return;
    }
    piVar1 = &DAT_00557c84;
    for (iVar2 = 0; iVar2 < DAT_004c3674; iVar2 = iVar2 + 1) {
      if (*piVar1 == DAT_00557c7c) {
        (&DAT_0059f162)[DAT_00557c7c * 0x2d8] = (char)piVar1[1];
        return;
      }
      piVar1 = piVar1 + 2;
    }
  }
  return;
}

