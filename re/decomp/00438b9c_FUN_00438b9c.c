// FUN_00438b9c @ 00438b9c size=541 sig=undefined FUN_00438b9c() cc=unknown
// callers: FUN_004393e8,FUN_00438fe0
// callees: FUN_0049eb44,FUN_00488aae,FUN_004893b4,FUN_004a6b00,FUN_0048905c,FUN_00489084,sprintf,FUN_00489232
// strings: \"%s*%s\"

undefined4 FUN_00438b9c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_458 [260];
  undefined1 local_354 [260];
  undefined1 local_250 [584];
  
  FUN_00488aae(&DAT_005594b4);
  iVar1 = FUN_0049eb44(DAT_004c4788,3,1,0x18,0,0);
  iVar3 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004c4788,3,1,0x27,0,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
  }
  sprintf(local_458,s__s__s_004c47a0,&DAT_005594b4,&DAT_005595b8);
  iVar1 = FUN_00489084(local_458,0,local_250);
  if (iVar1 == 0) {
    FUN_0049eb44(DAT_004c4788,5,1,10,0,0);
    FUN_0049eb44(DAT_004c4788,6,1,10,1,0);
  }
  else {
    while (iVar1 = FUN_00489232(local_250), iVar1 != 0) {
      FUN_004893b4(iVar1,local_458);
      iVar1 = FUN_0049eb44(DAT_004c4788,3,1,0x18,0,0);
      if (iVar1 == 0) {
        FUN_0049eb44(DAT_004c4788,3,1,0x26,0xffffffff,local_458);
      }
      else {
        iVar3 = 0;
        if (0 < iVar1) {
          do {
            FUN_0049eb44(DAT_004c4788,3,1,0x35,iVar3,local_354);
            iVar2 = FUN_004a6b00(local_458,local_354);
            if (iVar2 < 1) {
              FUN_0049eb44(DAT_004c4788,3,1,0x26,iVar3,local_458);
              break;
            }
            iVar3 = iVar3 + 1;
          } while (iVar3 < iVar1);
        }
        if (iVar1 == iVar3) {
          FUN_0049eb44(DAT_004c4788,3,1,0x26,0xffffffff,local_458);
        }
      }
    }
    FUN_0048905c(local_250);
    iVar1 = FUN_0049eb44(DAT_004c4788,3,1,0x18,0,0);
    if (iVar1 < 1) {
      FUN_0049eb44(DAT_004c4788,5,1,10,0,0);
      FUN_0049eb44(DAT_004c4788,6,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c4788,5,1,10,0,0);
      FUN_0049eb44(DAT_004c4788,6,1,10,0,0);
    }
  }
  FUN_0049eb44(DAT_004c4788,4,1,0x31,3,1);
  return 1;
}

