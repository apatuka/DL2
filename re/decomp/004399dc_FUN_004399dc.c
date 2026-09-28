// FUN_004399dc @ 004399dc size=1143 sig=undefined FUN_004399dc() cc=unknown
// callers: FUN_0043a1f8
// callees: FUN_0049eb44,FUN_004a2004,FUN_00436098,FUN_00436064,FUN_004a3de6,FUN_004a6b48,FUN_004360ec,FUN_004397a0,FUN_00414f04,FUN_004493dc
// strings: \"Load Custom Scenario\"|\"maps\\\\\"|\"Custom Map\"|\"Load Existing Map\"|\"saves\\\\\"|\"campaign\\\\\"|\"custom\\\\\"

undefined4 FUN_004399dc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined1 local_104 [256];
  
  bVar3 = DAT_004d59b4 != 0x2a;
  if (bVar3) {
    FUN_00436098();
    FUN_00436064();
  }
  DAT_005598e0 = (uint)bVar3;
  DAT_004c47fc = FUN_004a3de6(0,0x33323044);
  if (DAT_004c47fc == 0) {
    if ((DAT_005598e0 != 0) && (DAT_004d59b4 == 0x2a)) {
      FUN_004360ec();
    }
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005596c8 = DAT_004d59b4;
    DAT_004d59b4 = 0x42;
    FUN_00414f04(DAT_004c47fc);
    FUN_0049eb44(DAT_004c47fc,3,1,0x34,1,0);
    FUN_0049eb44(DAT_004c47fc,3,1,7,1,&LAB_004396ec);
    FUN_004a2004(DAT_004c47fc);
    if (DAT_004d5aa0 == '\0') {
      if ((param_1 == 3) || (param_1 == 5)) {
        FUN_0049eb44(DAT_004c47fc,9,1,10,1,0);
        FUN_0049eb44(DAT_004c47fc,8,1,10,1,0);
        FUN_0049eb44(DAT_004c47fc,7,1,10,1,0);
        FUN_0049eb44(DAT_004c47fc,2,1,0xf,0,PTR_s_Load_Custom_Scenario_00509cdc);
      }
      else {
        FUN_0049eb44(DAT_004c47fc,10,1,10,1,0);
      }
    }
    else {
      FUN_0049eb44(DAT_004c47fc,9,1,10,1,0);
      FUN_0049eb44(DAT_004c47fc,8,1,10,1,0);
    }
    if (DAT_004d5a88 == 0) {
      if (DAT_0058f1fc == 0) {
        FUN_004a6b48(&DAT_005596cc,s_saves__004c4822,0x104);
        DAT_005597d0 = DAT_004c482e;
        DAT_005597d4 = DAT_004c4832;
        DAT_005598dc = param_1;
        switch(param_1) {
        default:
          uVar2 = 7;
          FUN_004a6b48(&DAT_005596cc,s_saves__004c4822,0x104);
          DAT_005597d0 = DAT_004c482e;
          DAT_005597d4 = DAT_004c4832;
          break;
        case 1:
          uVar2 = 8;
          FUN_004a6b48(&DAT_005596cc,s_campaign__004c4833,0x104);
          DAT_005597d0 = DAT_004c483d;
          DAT_005597d4 = DAT_004c4841;
          break;
        case 2:
          uVar2 = 9;
          FUN_004a6b48(&DAT_005596cc,&DAT_004c4821,0x104);
          DAT_005597d0 = DAT_004c4829;
          DAT_005597d4 = DAT_004c482d;
          break;
        case 3:
          uVar2 = 10;
          FUN_004a6b48(&DAT_005596cc,s_custom__004c4842,0x104);
          DAT_005597d0 = DAT_004c484a;
          DAT_005597d4 = DAT_004c484e;
          break;
        case 5:
          uVar2 = 10;
          FUN_004a6b48(&DAT_005596cc,s_custom__004c4842,0x104);
          DAT_005597d0 = DAT_004c484a;
          DAT_005597d4 = DAT_004c484e;
        }
        FUN_0049eb44(DAT_004c47fc,uVar2,1,0xb,1,0);
        FUN_0049eb44(DAT_004c47fc,uVar2,1,0xe,0xff,local_104);
        FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_104);
      }
      else {
        FUN_004a6b48(&DAT_005596cc,&DAT_004c4821,0x104);
        DAT_005597d0 = DAT_004c4829;
        DAT_005597d4 = DAT_004c482d;
        FUN_0049eb44(DAT_004c47fc,9,1,0xb,1,0);
        FUN_0049eb44(DAT_004c47fc,9,1,0xe,0xff,local_104);
        FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,local_104);
        DAT_005598dc = 2;
      }
    }
    else {
      FUN_004a6b48(&DAT_005596cc,s_maps__004c4816,0x104);
      DAT_005597d0 = DAT_004c481c;
      DAT_005597d4 = DAT_004c4820;
      FUN_0049eb44(DAT_004c47fc,9,1,10,1,0);
      FUN_0049eb44(DAT_004c47fc,8,1,10,1,0);
      FUN_0049eb44(DAT_004c47fc,7,1,10,1,0);
      FUN_0049eb44(DAT_004c47fc,10,1,10,1,0);
      DAT_005598dc = 4;
      FUN_0049eb44(DAT_004c47fc,0xb,1,0xf,0,PTR_s_Custom_Map_00509d20);
      FUN_0049eb44(DAT_004c47fc,2,1,0xf,0,PTR_s_Load_Existing_Map_00509d3c);
    }
    iVar1 = FUN_004397a0();
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_0049eb44(DAT_004c47fc,3,1,0x1c,5,0);
      uVar2 = 1;
    }
  }
  return uVar2;
}

