// FUN_0041e9e8 @ 0041e9e8 size=670 sig=undefined FUN_0041e9e8() cc=unknown
// callers: FUN_0041edd8
// callees: FUN_00412584,FUN_0041e914,FUN_0041244c,FUN_004152e0,free,FUN_004b02a8,FUN_004152ec,FUN_00412654,FUN_00412e94,FUN_0049eb44,FUN_00412510,FUN_00412cd4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041e9e8(undefined1 *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_8 [4];
  
  DAT_004b7990 = 0;
  if (DAT_004b7988 != 0) {
    if (*(char *)(DAT_004b7988 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7988);
    }
    FUN_00412584(DAT_004b7988,3);
    DAT_004b7988 = 0;
  }
  if (DAT_004b798c != 0) {
    free(DAT_004b798c);
    DAT_004b798c = 0;
  }
  FUN_004152e0();
  switch(*param_1) {
  case 0x43:
    _DAT_0053b888 = 0;
    break;
  default:
    return 0;
  case 0x48:
    _DAT_0053b888 = 2;
    break;
  case 0x4d:
    _DAT_0053b888 = 3;
    break;
  case 0x4e:
    _DAT_0053b888 = 7;
    break;
  case 0x52:
    _DAT_0053b888 = 4;
    break;
  case 0x53:
    _DAT_0053b888 = 8;
    break;
  case 0x54:
    _DAT_0053b888 = 5;
    break;
  case 0x55:
    _DAT_0053b888 = 6;
    break;
  case 0x59:
    _DAT_0053b888 = 1;
  }
  if (param_2 == 0) {
    DAT_004b798c = FUN_0041244c(DAT_004d5a5c,param_1,local_8);
    if (DAT_004b798c == 0) {
      FUN_0049eb44(DAT_004b7974,9,1,0xf,0,&DAT_004b7a10);
    }
    else {
      FUN_0049eb44(DAT_004b7974,9,1,0xf,0,DAT_004b798c);
    }
  }
  else {
    FUN_0049eb44(DAT_004b7974,9,1,0xf,0,param_2);
  }
  if (DAT_004d59ac == 0) {
    FUN_0041e914();
    uVar1 = 1;
  }
  else if ((DAT_004d5aa8 == 0) || (DAT_004d5ab0 == 0)) {
    FUN_0041e914();
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_004b02a8(0x5a);
    if (iVar2 == 0) {
      DAT_004b7988 = 0;
    }
    else {
      DAT_004b7988 = FUN_00412510(iVar2);
    }
    if ((DAT_004b7988 == 0) && (DAT_004b798c == 0)) {
      FUN_004152ec();
      uVar1 = 0;
    }
    else if (DAT_004b7988 == 0) {
      FUN_0041e914();
      uVar1 = 1;
    }
    else {
      iVar2 = FUN_00412654(DAT_004b7988,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,param_1,&DAT_0065e644
                           ,0x14,0x4d);
      if (iVar2 == 0) {
        iVar2 = FUN_00412cd4(DAT_004b7988);
        if (iVar2 == 0) {
          if ((DAT_004d5ac4 == 0) && (param_2 == 0)) {
            FUN_0049eb44(DAT_004b7974,9,1,0xf,0,&DAT_004b7a10);
          }
          FUN_004152ec();
          uVar1 = 1;
        }
        else {
          FUN_00412584(DAT_004b7988,3);
          DAT_004b7988 = 0;
          FUN_0041e914();
          uVar1 = 1;
        }
      }
      else {
        FUN_00412584(DAT_004b7988,3);
        DAT_004b7988 = 0;
        FUN_0041e914();
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

