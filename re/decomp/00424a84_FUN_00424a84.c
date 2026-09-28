// FUN_00424a84 @ 00424a84 size=825 sig=undefined FUN_00424a84() cc=unknown
// callers: FUN_00425364
// callees: FUN_00424ec0,FUN_00412cd4,FUN_0041244c,FUN_00412654,FUN_004152ec,UpdateWindow,FUN_004b02a8,FUN_00412510,FUN_00424eb4,FUN_004249c0,FUN_0049eb44

undefined4 FUN_00424a84(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00557530 = 0;
  if (DAT_00557540 == 0) {
    DAT_00557540 = FUN_0041244c(DAT_004d5a5c,&DAT_00557534,auStack_18);
  }
  if (DAT_00557540 == 0) {
    FUN_0049eb44(DAT_004b7c80,2,1,0xf,0,&DAT_004b7cb8);
  }
  else {
    FUN_0049eb44(DAT_004b7c80,2,1,0xf,0,DAT_00557540);
  }
  if (DAT_004d59ac == 0) {
    FUN_004249c0();
    uVar1 = 1;
  }
  else if ((DAT_004d5aa8 == 0) || (DAT_004d5ab0 == 0)) {
    FUN_004249c0();
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_004b02a8(0x5a);
    if (iVar2 == 0) {
      DAT_00557530 = 0;
    }
    else {
      DAT_00557530 = FUN_00412510(iVar2);
    }
    if ((DAT_00557530 == 0) && (DAT_00557540 == 0)) {
      FUN_004152ec();
      uVar1 = 0;
    }
    else if (DAT_00557530 == 0) {
      FUN_004249c0();
      uVar1 = 1;
    }
    else {
      if ((DAT_004d5ac4 == 0) && (DAT_0055754c == 0)) {
        FUN_0049eb44(DAT_004b7c80,1,1,0x42,0,0x3f2);
      }
      local_10 = 10;
      local_14 = 0xd;
      local_8 = 0xd2;
      local_c = 0xd5;
      FUN_0049eb44(DAT_004b7c80,*(undefined4 *)(&DAT_004b7c94 + DAT_00557544 * 4),1,0xd,0,&local_14)
      ;
      FUN_0049eb44(DAT_004b7c80,2,1,0x3c,0,0);
      FUN_00424ec0();
      FUN_00424eb4();
      UpdateWindow(DAT_004d5974);
      local_14 = 10000;
      local_10 = 10000;
      local_c = 0x27d8;
      local_8 = 0x27d8;
      iVar2 = FUN_00412654(DAT_00557530,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,&DAT_00557534,
                           &DAT_0065e644,DAT_004b7c88 + 0xd,DAT_004b7c84 + 10);
      if (iVar2 == 0) {
        iVar2 = FUN_00412cd4(DAT_00557530);
        if (iVar2 == 0) {
          FUN_0049eb44(DAT_004b7c80,*(undefined4 *)(&DAT_004b7c94 + DAT_00557544 * 4),1,0xd,0,
                       &local_14);
          if ((DAT_004d5ac4 != 0) || (DAT_0055754c != 0)) {
            FUN_0049eb44(DAT_004b7c80,1,1,0x42,0,1000);
            FUN_0049eb44(DAT_004b7c80,2,1,0x3c,1,0);
          }
          FUN_004152ec();
          uVar1 = 1;
        }
        else {
          FUN_0049eb44(DAT_004b7c80,2,1,0x3c,1,0);
          FUN_0049eb44(DAT_004b7c80,*(undefined4 *)(&DAT_004b7c94 + DAT_00557544 * 4),1,0xd,0,
                       &local_14);
          FUN_0049eb44(DAT_004b7c80,1,1,0x42,0,1000);
          FUN_004249c0();
          uVar1 = 1;
        }
      }
      else {
        FUN_0049eb44(DAT_004b7c80,2,1,0x3c,1,0);
        FUN_0049eb44(DAT_004b7c80,*(undefined4 *)(&DAT_004b7c94 + DAT_00557544 * 4),1,0xd,0,
                     &local_14);
        FUN_0049eb44(DAT_004b7c80,1,1,0x42,0,1000);
        FUN_004249c0();
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

