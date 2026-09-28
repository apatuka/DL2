// FUN_00421b24 @ 00421b24 size=729 sig=undefined FUN_00421b24() cc=unknown
// callers: FUN_00422f7c
// callees: FUN_00412cd4,FUN_0041244c,FUN_00421a54,FUN_00412654,FUN_004152ec,FUN_00412584,free,FUN_004b02a8,FUN_00412510,FUN_004152e0,FUN_00412e94,FUN_0049eb44

undefined4 FUN_00421b24(undefined1 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  
  DAT_004b7b60 = 0;
  if (DAT_004b7b58 != 0) {
    if (*(char *)(DAT_004b7b58 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7b58);
    }
    FUN_00412584(DAT_004b7b58,3);
    DAT_004b7b58 = 0;
  }
  if (DAT_004b7b5c != 0) {
    free(DAT_004b7b5c);
    DAT_004b7b5c = 0;
  }
  if (DAT_0053c4dc != 0) {
    FUN_004152e0();
  }
  local_18 = 10000;
  local_14 = 10000;
  local_c = 0x27d8;
  local_10 = 0x27d8;
  FUN_0049eb44(DAT_004b7b50,
               *(undefined4 *)(&DAT_004b7b68 + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 4),1,
               0xd,0,&local_18);
  switch(*param_1) {
  case 0x43:
    DAT_005574ec = 0;
    break;
  default:
    return 0;
  case 0x48:
    DAT_005574ec = 2;
    break;
  case 0x4d:
    DAT_005574ec = 3;
    break;
  case 0x4e:
    DAT_005574ec = 7;
    break;
  case 0x52:
    DAT_005574ec = 4;
    break;
  case 0x53:
    DAT_005574ec = 8;
    break;
  case 0x54:
    DAT_005574ec = 5;
    break;
  case 0x55:
    DAT_005574ec = 6;
    break;
  case 0x59:
    DAT_005574ec = 1;
  }
  DAT_004b7b5c = FUN_0041244c(DAT_004d5a5c,param_1,local_8);
  if (DAT_004b7b5c == 0) {
    FUN_0049eb44(DAT_004b7b50,2,1,0xf,0,&DAT_004b7b84);
  }
  else {
    FUN_0049eb44(DAT_004b7b50,2,1,0xf,0,DAT_004b7b5c);
  }
  if (DAT_004d59ac == 0) {
    FUN_00421a54();
    uVar1 = 1;
  }
  else if ((DAT_004d5aa8 == 0) || (DAT_004d5ab0 == 0)) {
    FUN_00421a54();
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_004b02a8(0x5a);
    if (iVar2 == 0) {
      DAT_004b7b58 = 0;
    }
    else {
      DAT_004b7b58 = FUN_00412510(iVar2);
    }
    if ((DAT_004b7b58 == 0) && (DAT_004b7b5c == 0)) {
      FUN_004152ec();
      uVar1 = 0;
    }
    else if (DAT_004b7b58 == 0) {
      FUN_00421a54();
      uVar1 = 1;
    }
    else {
      iVar2 = FUN_00412654(DAT_004b7b58,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,param_1,&DAT_0065e644
                           ,0x10,0x53);
      if (iVar2 == 0) {
        iVar2 = FUN_00412cd4(DAT_004b7b58);
        if (iVar2 == 0) {
          if (DAT_004d5ac4 == 0) {
            FUN_0049eb44(DAT_004b7b50,2,1,0xf,0,&DAT_004b7b84);
          }
          FUN_004152ec();
          uVar1 = 1;
        }
        else {
          FUN_00412584(DAT_004b7b58,3);
          DAT_004b7b58 = 0;
          FUN_00421a54();
          uVar1 = 1;
        }
      }
      else {
        FUN_00412584(DAT_004b7b58,3);
        DAT_004b7b58 = 0;
        FUN_00421a54();
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

