// FUN_00422bd8 @ 00422bd8 size=251 sig=undefined FUN_00422bd8() cc=unknown
// callers: FUN_00423104,CheckEventLog
// callees: FUN_004227f0,FUN_00422344,FUN_004225ec,FUN_00421efc,FUN_0049eb44,FUN_00421fb4

void FUN_00422bd8(int param_1)

{
  char cVar1;
  
  DAT_004b7b44 = param_1;
  if (param_1 == 0) {
    cVar1 = FUN_00421efc();
    if (cVar1 != '\0') {
      FUN_0049eb44(DAT_004b7b50,4,1,10,0,0);
      goto LAB_00422c23;
    }
  }
  FUN_0049eb44(DAT_004b7b50,4,1,10,1,0);
LAB_00422c23:
  if ((DAT_004b7b44 == 0) && (DAT_0053b8cc != '\0')) {
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7b50,3,1,0x3c,1,1);
    FUN_00421fb4();
  }
  else {
    FUN_0049eb44(DAT_004b7b50,3,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x3c,1,1);
    FUN_004227f0();
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x1b,0,0);
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x21,0,1);
  }
  FUN_004225ec();
  FUN_00422344();
  return;
}

