// FUN_0042540c @ 0042540c size=529 sig=undefined FUN_0042540c() cc=unknown
// callers: FUN_00425ac4
// callees: FUN_00412cd4,FUN_0041244c,FUN_00412654,FUN_004152ec,FUN_00412584,free,FUN_004b02a8,FUN_00412510,FUN_004152e0,FUN_004253d8,FUN_00412e94,FUN_0049eb44

undefined4 FUN_0042540c(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_8 [4];
  
  DAT_004b7d00 = 0;
  if (DAT_004b7cf8 != 0) {
    if (*(char *)(DAT_004b7cf8 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7cf8);
    }
    FUN_00412584(DAT_004b7cf8,3);
    DAT_004b7cf8 = 0;
  }
  if (DAT_004b7cfc != 0) {
    free(DAT_004b7cfc);
    DAT_004b7cfc = 0;
  }
  if (DAT_004b7d0c != 0) {
    FUN_004152e0();
  }
  FUN_0049eb44(DAT_004b7ce4,3,1,0x3c,0,2);
  DAT_004b7cfc = FUN_0041244c(DAT_004d5a5c,param_1,local_8);
  if (DAT_004b7cfc == 0) {
    FUN_0049eb44(DAT_004b7ce4,4,1,0xf,0,&DAT_004b7d10);
  }
  else {
    FUN_0049eb44(DAT_004b7ce4,4,1,0xf,0,DAT_004b7cfc);
  }
  if (DAT_004d59ac == 0) {
    FUN_004253d8();
    uVar1 = 1;
  }
  else if ((DAT_004d5aa8 == 0) || (DAT_004d5ab0 == 0)) {
    FUN_004253d8();
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_004b02a8(0x5a);
    if (iVar2 == 0) {
      DAT_004b7cf8 = 0;
    }
    else {
      DAT_004b7cf8 = FUN_00412510(iVar2);
    }
    if ((DAT_004b7cf8 == 0) && (DAT_004b7cfc == 0)) {
      FUN_004152ec();
      uVar1 = 0;
    }
    else if (DAT_004b7cf8 == 0) {
      FUN_004253d8();
      uVar1 = 1;
    }
    else {
      iVar2 = FUN_00412654(DAT_004b7cf8,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,param_1,&DAT_0065e644
                           ,0xc,0xcf);
      if (iVar2 == 0) {
        iVar2 = FUN_00412cd4(DAT_004b7cf8);
        if (iVar2 == 0) {
          if (DAT_004d5ac4 == 0) {
            FUN_0049eb44(DAT_004b7ce4,4,1,0xf,0,&DAT_004b7d10);
          }
          FUN_004152ec();
          uVar1 = 1;
        }
        else {
          FUN_00412584(DAT_004b7cf8,3);
          DAT_004b7cf8 = 0;
          FUN_004253d8();
          uVar1 = 1;
        }
      }
      else {
        FUN_00412584(DAT_004b7cf8,3);
        DAT_004b7cf8 = 0;
        FUN_004253d8();
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

