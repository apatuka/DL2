// FUN_00430cd8 @ 00430cd8 size=878 sig=undefined FUN_00430cd8() cc=unknown
// callers: FUN_00435ed0,FUN_00431128
// callees: FUN_00430c38,free,FUN_004b02a8,FUN_00412510,FUN_004152ec,FUN_0049eb44,FUN_00412654,FUN_00412cd4,FUN_0041244c,FUN_00412e94,FUN_00412584

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00430cd8(undefined1 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  
  DAT_004c42ec = 0;
  if (DAT_004c42e4 != 0) {
    if (*(char *)(DAT_004c42e4 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004c42e4);
    }
    FUN_00412584(DAT_004c42e4,3);
    DAT_004c42e4 = 0;
  }
  if (DAT_004c42e8 != 0) {
    free(DAT_004c42e8);
    DAT_004c42e8 = 0;
  }
  switch(*param_1) {
  case 0x43:
    _DAT_00558cc8 = 0;
    break;
  default:
    return 0;
  case 0x48:
    _DAT_00558cc8 = 2;
    break;
  case 0x4d:
    _DAT_00558cc8 = 3;
    break;
  case 0x4e:
    _DAT_00558cc8 = 7;
    break;
  case 0x52:
    _DAT_00558cc8 = 4;
    break;
  case 0x53:
    _DAT_00558cc8 = 8;
    break;
  case 0x54:
    _DAT_00558cc8 = 5;
    break;
  case 0x55:
    _DAT_00558cc8 = 6;
    break;
  case 0x59:
    _DAT_00558cc8 = 1;
  }
  if (DAT_00558d58 == 0) {
    uVar3 = 3;
    uVar1 = DAT_004c42d4;
  }
  else if (DAT_00558d58 == 1) {
    uVar3 = 3;
    uVar1 = DAT_004c42d8;
  }
  else if (DAT_00558d58 == 2) {
    uVar3 = 3;
    uVar1 = DAT_004c42dc;
  }
  else {
    uVar3 = 4;
    uVar1 = DAT_004c42e0;
  }
  DAT_004c42e8 = FUN_0041244c(DAT_004d5a5c,param_1,local_8);
  if (DAT_004c42e8 == 0) {
    FUN_0049eb44(uVar1,uVar3,1,0xf,0,&DAT_004c4588);
  }
  else {
    FUN_0049eb44(uVar1,uVar3,1,0xf,0,DAT_004c42e8);
  }
  if (DAT_004d59ac == 0) {
    FUN_00430c38();
    uVar1 = 1;
  }
  else if ((DAT_004d5ab0 == 0) || (DAT_004d5aa8 == 0)) {
    FUN_00430c38();
    uVar1 = 1;
  }
  else {
    local_14 = 10000;
    local_18 = 10000;
    local_c = 0x27d8;
    local_10 = 0x27d8;
    uVar1 = DAT_004c42d4;
    if (((DAT_00558d58 != 0) && (uVar1 = DAT_004c42d8, DAT_00558d58 != 1)) &&
       (uVar1 = DAT_004c42dc, DAT_00558d58 != 2)) {
      uVar1 = DAT_004c42e0;
    }
    FUN_0049eb44(uVar1,0xd,1,0xd,0,&local_18);
    iVar2 = FUN_004b02a8(0x5a);
    if (iVar2 == 0) {
      DAT_004c42e4 = 0;
    }
    else {
      DAT_004c42e4 = FUN_00412510(iVar2);
    }
    if ((DAT_004c42e4 == 0) && (DAT_004c42e8 == 0)) {
      FUN_004152ec();
      uVar1 = 0;
    }
    else if (DAT_004c42e4 == 0) {
      FUN_00430c38();
      uVar1 = 1;
    }
    else {
      iVar2 = FUN_00412654(DAT_004c42e4,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,param_1,&DAT_0065e644
                           ,10,7);
      if (iVar2 == 0) {
        iVar2 = FUN_00412cd4(DAT_004c42e4);
        if (iVar2 == 0) {
          if (DAT_00558d58 == 0) {
            uVar3 = 3;
            uVar1 = DAT_004c42d4;
          }
          else if (DAT_00558d58 == 1) {
            uVar3 = 3;
            uVar1 = DAT_004c42d8;
          }
          else if (DAT_00558d58 == 2) {
            uVar3 = 3;
            uVar1 = DAT_004c42dc;
          }
          else {
            uVar3 = 4;
            uVar1 = DAT_004c42e0;
          }
          if (DAT_004d5ac4 == 0) {
            FUN_0049eb44(uVar1,uVar3,1,0xf,0,&DAT_004c4588);
          }
          FUN_004152ec();
          uVar1 = 1;
        }
        else {
          FUN_00412584(DAT_004c42e4,3);
          DAT_004c42e4 = 0;
          FUN_00430c38();
          uVar1 = 1;
        }
      }
      else {
        FUN_00412584(DAT_004c42e4,3);
        DAT_004c42e4 = 0;
        FUN_00430c38();
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

