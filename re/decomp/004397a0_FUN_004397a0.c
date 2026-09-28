// FUN_004397a0 @ 004397a0 size=476 sig=undefined FUN_004397a0() cc=unknown
// callers: FUN_004399dc,FUN_00439e98
// callees: FUN_0049eb44,FUN_00488aae,FUN_004893b4,FUN_004a6b00,FUN_0048905c,FUN_00489084,sprintf,FUN_00489232
// strings: \"%s*%s\"

undefined4 FUN_004397a0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_458 [260];
  undefined1 local_354 [260];
  undefined1 local_250 [584];
  
  FUN_00488aae(&DAT_005596cc);
  iVar1 = FUN_0049eb44(DAT_004c47fc,3,1,0x18,0,0);
  iVar3 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004c47fc,3,1,0x27,0,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
  }
  sprintf(local_458,s__s__s_004c4810,&DAT_005596cc,&DAT_005597d0);
  iVar1 = FUN_00489084(local_458,0,local_250);
  if (iVar1 == 0) {
    FUN_0049eb44(DAT_004c47fc,5,1,10,1,0);
  }
  else {
    while (iVar1 = FUN_00489232(local_250), iVar1 != 0) {
      FUN_004893b4(iVar1,local_458);
      iVar1 = FUN_0049eb44(DAT_004c47fc,3,1,0x18,0,0);
      if (iVar1 == 0) {
        FUN_0049eb44(DAT_004c47fc,3,1,0x26,0xffffffff,local_458);
      }
      else {
        iVar3 = 0;
        if (0 < iVar1) {
          do {
            FUN_0049eb44(DAT_004c47fc,3,1,0x35,iVar3,local_354);
            iVar2 = FUN_004a6b00(local_458,local_354);
            if (iVar2 < 1) {
              FUN_0049eb44(DAT_004c47fc,3,1,0x26,iVar3,local_458);
              break;
            }
            iVar3 = iVar3 + 1;
          } while (iVar3 < iVar1);
        }
        if (iVar1 == iVar3) {
          FUN_0049eb44(DAT_004c47fc,3,1,0x26,0xffffffff,local_458);
        }
      }
    }
    FUN_0048905c(local_250);
    iVar1 = FUN_0049eb44(DAT_004c47fc,3,1,0x18,0,0);
    if (iVar1 < 1) {
      FUN_0049eb44(DAT_004c47fc,5,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c47fc,5,1,10,0,0);
    }
  }
  FUN_0049eb44(DAT_004c47fc,4,1,0x31,3,1);
  return 1;
}

