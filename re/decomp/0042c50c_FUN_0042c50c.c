// FUN_0042c50c @ 0042c50c size=494 sig=undefined FUN_0042c50c() cc=unknown
// callers: FUN_0042d3dc
// callees: FUN_0042c448,FUN_00412510,FUN_00412654,FUN_00412cd4,FUN_0041244c,FUN_004b02a8,FUN_0049eb44,FUN_004152e0,FUN_004152ec

undefined8 FUN_0042c50c(void)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uStack_c;
  
  puVar1 = DAT_00557c50;
  FUN_004152e0();
  switch(*puVar1) {
  case 0x43:
    DAT_00557c44 = 0;
    break;
  default:
    uVar2 = 0;
    goto LAB_0042c735;
  case 0x48:
    DAT_00557c44 = 2;
    break;
  case 0x4d:
    DAT_00557c44 = 3;
    break;
  case 0x4e:
    DAT_00557c44 = 7;
    break;
  case 0x52:
    DAT_00557c44 = 4;
    break;
  case 0x53:
    DAT_00557c44 = 8;
    break;
  case 0x54:
    DAT_00557c44 = 5;
    break;
  case 0x55:
    DAT_00557c44 = 6;
    break;
  case 0x59:
    DAT_00557c44 = 1;
  }
  DAT_00557c4c = FUN_0041244c(DAT_004d5a5c,puVar1,&uStack_c);
  if (DAT_00557c4c != 0) {
    FUN_0049eb44(DAT_004bf8fc,0x27,1,0xf,0,DAT_00557c4c);
  }
  if (DAT_004d59ac == 0) {
    FUN_0042c448();
    uVar2 = 1;
  }
  else if ((DAT_004d5aa8 == 0) || (DAT_004d5ab0 == 0)) {
    FUN_0042c448();
    uVar2 = 1;
  }
  else {
    iVar3 = FUN_004b02a8(0x5a);
    if (iVar3 == 0) {
      DAT_00557c48 = 0;
    }
    else {
      DAT_00557c48 = FUN_00412510(iVar3);
    }
    if ((DAT_00557c48 == 0) && (DAT_00557c4c == 0)) {
      FUN_004152ec();
      uVar2 = 0;
    }
    else if (DAT_00557c48 == 0) {
      FUN_0042c448();
      uVar2 = 1;
    }
    else {
      iVar3 = FUN_00412654(DAT_00557c48,DAT_004d5a74,DAT_004d5a68,DAT_004d5a6c,puVar1,&DAT_0065e644,
                           0x1a8,0x99);
      if (iVar3 == 0) {
        iVar3 = FUN_00412cd4(DAT_00557c48);
        if (iVar3 == 0) {
          if (DAT_004d5ac4 == 0) {
            FUN_0049eb44(DAT_004bf8fc,0x27,1,0xf,0,&DAT_004c0099);
          }
          FUN_004152ec();
          uVar2 = 1;
        }
        else {
          FUN_0042c448();
          uVar2 = 1;
        }
      }
      else {
        FUN_0042c448();
        uVar2 = 1;
      }
    }
  }
LAB_0042c735:
  return CONCAT44(uStack_c,uVar2);
}

