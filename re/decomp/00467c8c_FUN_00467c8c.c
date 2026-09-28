// FUN_00467c8c @ 00467c8c size=229 sig=undefined FUN_00467c8c() cc=unknown
// callers: 
// callees: FUN_0046ca40,FUN_00463a74,FUN_004363f8,memcpy

undefined4 FUN_00467c8c(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 auStack_400 [1024];
  
  uVar2 = FUN_0046ca40();
  DAT_004d5b1c = (undefined1)((ulonglong)uVar2 % 6);
  DAT_004d5a50 = 0;
  DAT_004d5a4c = 0;
  DAT_004d5a58 = 0;
  DAT_004d5a88 = 0;
  DAT_005597d5 = 0x30;
  DAT_004d5aa0 = 0;
  DAT_0058f1ec = 0;
  DAT_004d5140 = 0;
  if (DAT_004d5aec < 2) {
    DAT_004d5aec = 2;
  }
  DAT_004ca3ac = 0;
  DAT_0058ed2e = 0;
  DAT_004d513c = 0;
  DAT_0058f12e = 0;
  memcpy(&DAT_0051a8cc,&DAT_0051accc,0x3b0);
  FUN_00463a74();
  if (DAT_004d59a8 == 0) {
    uVar3 = FUN_004363f8();
  }
  else if (((DAT_004d59a8 & 0x10) == 0) || ((DAT_004d59a8 & 2) == 0)) {
    uVar3 = 5;
  }
  else {
    uVar3 = 0xb;
  }
  switch(uVar3) {
  case 4:
    uVar3 = 0x2c;
    break;
  case 5:
    uVar3 = 0x37;
    break;
  case 6:
    FUN_00467b2c();
    uVar3 = 0x43;
    break;
  case 7:
    FUN_004780e4(DAT_0058f1f4,1);
    sprintf(auStack_400,s__stutorial_SAV_004d5209,&DAT_0058f20c);
    iVar4 = FUN_004618e8(auStack_400,1);
    if (iVar4 == 0) {
      uVar3 = 0x35;
    }
    else {
      DAT_004d5ae0 = 2;
      DAT_004d598c = 1;
      DAT_004ca3ac = 1;
      uVar3 = 0x46;
    }
    break;
  default:
    uVar3 = 0x33;
    break;
  case 9:
    FUN_0042ec70();
    uVar3 = 0x35;
    break;
  case 10:
    DAT_004d5aa0 = 1;
    uVar3 = 0x2f;
    break;
  case 0xb:
    uVar3 = 0x2e;
    break;
  case 0xc:
    cVar1 = FUN_00467884();
    if (cVar1 == '\0') {
      uVar3 = 0x35;
    }
    else {
      uVar3 = 0x33;
    }
  }
  return uVar3;
}

