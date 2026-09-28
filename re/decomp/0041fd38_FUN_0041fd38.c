// FUN_0041fd38 @ 0041fd38 size=478 sig=undefined FUN_0041fd38() cc=unknown
// callers: CheckColonyAssistant,FUN_00421828,FUN_004202cc
// callees: FUN_0041ff24,FUN_0041ff18,FUN_0041ff98,FUN_0049eb44,FUN_0041ffd4

void FUN_0041fd38(int param_1,char param_2)

{
  DAT_0053b8ac = param_1;
  if (((param_1 < 0x16) && (DAT_0053b8c4 == '\x01')) && (param_2 != '\0')) {
    DAT_0053b8c4 = '\0';
    FUN_0049eb44(DAT_004b7a14,6,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7a14,7,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7a14,8,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7a14,9,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7a14,0xb,1,0x3c,0,1);
    FUN_0049eb44(DAT_004b7a14,0xc,1,0x3c,0,1);
  }
  else if ((0x16 < param_1) && (param_1 < 0x1c)) {
    if ((DAT_0053b8c4 == '\0') && (param_2 != '\0')) {
      DAT_0053b8c4 = '\x01';
      FUN_0049eb44(DAT_004b7a14,6,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,7,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,8,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,9,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,0xb,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,0xc,1,0x3c,1,1);
    }
    if ((1 << ((char)DAT_0053b8ac - 0x16U & 0x1f) & (int)*(char *)(DAT_0053b8b8 + 0x9ae)) == 0) {
      FUN_0049eb44(DAT_004b7a14,7,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7a14,7,1,0xb,1,0);
    }
    FUN_0041ff98();
    FUN_0041ffd4();
  }
  FUN_0041ff24();
  FUN_0041ff18();
  return;
}

