// FUN_0043c260 @ 0043c260 size=692 sig=undefined FUN_0043c260() cc=unknown
// callers: FUN_0046f5d4
// callees: FUN_004a3de6,FUN_0048e11b,FUN_004a2004,FUN_00414f04,FUN_0049eb44

undefined4 FUN_0043c260(void)

{
  int iVar1;
  
  FUN_0048e11b();
  if (DAT_004d5aa0 == '\0') {
    DAT_00559da4 = 0x30303044;
  }
  else {
    DAT_00559da4 = 0x30323944;
  }
  if (DAT_004c48a0 == 0) {
    DAT_004c48a0 = FUN_004a3de6(0,DAT_00559da4);
    if (DAT_004c48a0 == 0) {
      return 0;
    }
  }
  FUN_00414f04(DAT_004c48a0);
  if (DAT_004d5aa0 == '\0') {
    FUN_0049eb44(DAT_004c48a0,2,1,0x42,0,DAT_004d5b1c + 0x406);
    FUN_004a2004(DAT_004c48a0);
    FUN_0049eb44(DAT_004c48a0,0x16,1,0xb,DAT_004c48a4 != 0,0);
    iVar1 = 1000;
    do {
      FUN_0049eb44(DAT_004c48a0,iVar1,1,7,0,FUN_0043b8b0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x3f2);
    FUN_0049eb44(DAT_004c48a0,0xc,1,7,0,FUN_0043aed0);
    FUN_0049eb44(DAT_004c48a0,0x15,1,7,0,FUN_0043b040);
    FUN_0049eb44(DAT_004c48a0,0x24,1,7,0,FUN_0043b2c4);
    FUN_0049eb44(DAT_004c48a0,0x25,1,7,0,FUN_0043b50c);
    FUN_0049eb44(DAT_004c48a0,0x14,1,7,0,FUN_0043b1ac);
    FUN_0049eb44(DAT_004c48a0,0x2d,1,7,0,FUN_0043ae78);
    FUN_0049eb44(DAT_004c48a0,0x18,1,7,0,FUN_00414bd8);
    FUN_0049eb44(DAT_004c48a0,0x19,1,7,0,FUN_00414dd4);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,2,1,0x42,0,DAT_004d5b1c + 0x406);
    FUN_004a2004(DAT_004c48a0);
    FUN_0049eb44(DAT_004c48a0,0x14,1,0xb,DAT_004c48a4 != 0,0);
    iVar1 = 1000;
    do {
      FUN_0049eb44(DAT_004c48a0,iVar1,1,7,0,FUN_0043b8b0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x3f2);
    FUN_0049eb44(DAT_004c48a0,0xc,1,7,0,FUN_0043aed0);
    FUN_0049eb44(DAT_004c48a0,0x22,1,7,0,FUN_0043addc);
    FUN_0049eb44(DAT_004c48a0,0x25,1,7,0,FUN_0043b2c4);
    FUN_0049eb44(DAT_004c48a0,0x26,1,7,0,FUN_0043b50c);
    FUN_0049eb44(DAT_004c48a0,0x13,1,7,0,FUN_0043b1ac);
    FUN_0049eb44(DAT_004c48a0,0x2e,1,7,0,FUN_0043ae78);
  }
  return 1;
}

