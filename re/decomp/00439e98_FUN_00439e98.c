// FUN_00439e98 @ 00439e98 size=840 sig=undefined FUN_00439e98() cc=unknown
// callers: FUN_0043a1f8
// callees: FUN_0049eb44,FUN_0049117e,FUN_00458bc8,FUN_0042836c,FUN_0048db5d,FUN_0043997c,FUN_004a6b48,sprintf,FUN_004397a0,FUN_004a2cb5
// strings: \"saves\\\\\"|\"campaign\\\\\"|\"custom\\\\\"|\"%s%s%s\"

int FUN_00439e98(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_110;
  undefined1 local_10c [260];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0043997c();
  iVar1 = FUN_004a2cb5(DAT_004c47fc,&local_110);
  if (((iVar1 == 0) && (local_110 != 0)) && (*(int *)(DAT_004c47fc + 100) == 0)) {
    switch(local_110) {
    case 5:
      if (((DAT_005598dc != 2) && (DAT_005598dc != 5)) || (iVar1 = FUN_00458bc8(), 2 < iVar1)) {
        uVar2 = FUN_0049eb44(DAT_004c47fc,3,1,0x22,0,0);
        FUN_0049eb44(DAT_004c47fc,3,1,0x35,uVar2,local_10c);
        sprintf(&DAT_005597d5,s__s_s_s_004c484f,&DAT_005596cc,local_10c,&DAT_005597d0);
        DAT_004d59a4 = 0;
        return local_110;
      }
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 4;
      uVar2 = FUN_0049117e(0,0x54415453,3);
      uVar3 = FUN_0049117e(0,0x54415453,2);
      FUN_0042836c(uVar3,uVar2,uVar4,uVar5,uVar6);
      break;
    case 6:
      DAT_004d59a4 = 0;
      return local_110;
    case 7:
      FUN_004a6b48(&DAT_005596cc,s_saves__004c4822,0x104);
      DAT_005597d0 = DAT_004c482e;
      DAT_005597d4 = DAT_004c4832;
      FUN_0049eb44(DAT_004c47fc,7,1,0xe,0x103,local_10c);
      FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_10c);
      FUN_004397a0();
      FUN_0049eb44(DAT_004c47fc,3,1,0x1c,5,0);
      DAT_005598dc = 0;
      break;
    case 8:
      FUN_004a6b48(&DAT_005596cc,s_campaign__004c4833,0x104);
      DAT_005597d0 = DAT_004c483d;
      DAT_005597d4 = DAT_004c4841;
      FUN_0049eb44(DAT_004c47fc,8,1,0xe,0x103,local_10c);
      FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_10c);
      FUN_004397a0();
      FUN_0049eb44(DAT_004c47fc,3,1,0x1c,5,0);
      DAT_005598dc = 1;
      break;
    case 9:
      FUN_004a6b48(&DAT_005596cc,&DAT_004c4821,0x104);
      DAT_005597d0 = DAT_004c4829;
      DAT_005597d4 = DAT_004c482d;
      FUN_0049eb44(DAT_004c47fc,9,1,0xe,0x103,local_10c);
      FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_10c);
      FUN_004397a0();
      FUN_0049eb44(DAT_004c47fc,3,1,0x1c,5,0);
      DAT_005598dc = 2;
      break;
    case 10:
      FUN_004a6b48(&DAT_005596cc,s_custom__004c4842,0x104);
      DAT_005597d0 = DAT_004c484a;
      DAT_005597d4 = DAT_004c484e;
      FUN_0049eb44(DAT_004c47fc,10,1,0xe,0x103,local_10c);
      FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_10c);
      FUN_004397a0();
      FUN_0049eb44(DAT_004c47fc,3,1,0x1c,5,0);
      if (DAT_005598dc != 5) {
        DAT_005598dc = 3;
      }
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

