// FUN_00438fe0 @ 00438fe0 size=959 sig=undefined FUN_00438fe0() cc=unknown
// callers: FUN_004396a0
// callees: FUN_004893b4,FUN_004a2004,FUN_004a3de6,sprintf,FUN_004360ec,FUN_00414f04,FUN_004493dc,FUN_0049eb44,FUN_004a60b1,FUN_00436098,FUN_00436064,FUN_00438b9c,FUN_004a6b48,FUN_0046ca40
// strings: \"map%d%s\"|\"maps\\\\\"|\"custom\\\\\"|\"campaign\\\\\"|\"saves\\\\\"|\"%s%s%s\"|\"%sMyGame%s\"

undefined4 FUN_00438fe0(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined1 local_21c [260];
  undefined1 local_118 [260];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  bVar4 = DAT_004d59b4 != 0x2a;
  if (bVar4) {
    FUN_00436098();
    FUN_00436064();
  }
  DAT_004c479c = (uint)bVar4;
  DAT_004c4788 = FUN_004a3de6(0,0x32323044);
  if (DAT_004c4788 == 0) {
    if ((DAT_004c479c != 0) && (DAT_004d59b4 == 0x2a)) {
      FUN_004360ec();
    }
    uVar3 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005594b0 = DAT_004d59b4;
    DAT_004d59b4 = 0x4f;
    FUN_00414f04(DAT_004c4788);
    local_14 = DAT_004c4790;
    local_10 = DAT_004c478c;
    local_c = DAT_004c4798;
    local_8 = DAT_004c4794;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004c4788);
    FUN_0049eb44(DAT_004c4788,3,1,0x34,1,0);
    FUN_0049eb44(DAT_004c4788,0xf,1,7,0,FUN_00438f58);
    if (DAT_004d5aa0 == '\0') {
      FUN_0049eb44(DAT_004c4788,8,1,10,1,0);
      FUN_0049eb44(DAT_004c4788,10,1,10,1,0);
      FUN_0049eb44(DAT_004c4788,9,1,10,1,0);
      FUN_0049eb44(DAT_004c4788,0xb,1,10,1,0);
      if (DAT_0058f1fc == 0) {
        if (DAT_004d5a94 < 1) {
          FUN_004a6b48(&DAT_005594b4,s_saves__004c47c7,0x104);
          DAT_005595b8 = DAT_004c47e2;
          DAT_005595bc = DAT_004c47e6;
        }
        else {
          FUN_004a6b48(&DAT_005594b4,s_campaign__004c47d3,0x104);
          DAT_005595b8 = DAT_004c47dd;
          DAT_005595bc = DAT_004c47e1;
        }
      }
      else {
        FUN_004a6b48(&DAT_005594b4,&DAT_004c47c6,0x104);
        DAT_005595b8 = DAT_004c47ce;
        DAT_005595bc = DAT_004c47d2;
      }
    }
    else if (DAT_004d5aec < 2) {
      DAT_005596c4 = 1;
      uVar1 = FUN_0046ca40(&DAT_004c47ae);
      sprintf(param_1,s_map_d_s_004c47a6,uVar1 % 100);
      FUN_0049eb44(DAT_004c4788,8,1,10,1,0);
      FUN_0049eb44(DAT_004c4788,9,1,10,1,0);
      FUN_0049eb44(DAT_004c4788,10,1,0xb,1,0);
      FUN_004a6b48(&DAT_005594b4,s_maps__004c47b3,0x104);
      DAT_005595b8 = DAT_004c47ae;
      DAT_005595bc = DAT_004c47b2;
    }
    else {
      DAT_005596c4 = 0;
      FUN_0049eb44(DAT_004c4788,8,1,0xb,1,0);
      FUN_004a6b48(&DAT_005594b4,s_custom__004c47b9,0x104);
      DAT_005595b8 = DAT_004c47c1;
      DAT_005595bc = DAT_004c47c5;
    }
    iVar2 = FUN_00438b9c();
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      FUN_0049eb44(DAT_004c4788,3,1,7,0,FUN_00438dbc);
      FUN_0049eb44(DAT_004c4788,3,1,0x1c,3,0);
      if (param_1 == 0) {
        sprintf(local_118,s__sMyGame_s_004c47ee,&DAT_005594b4,&DAT_005595b8);
      }
      else {
        FUN_004893b4(param_1,local_21c);
        sprintf(local_118,s__s_s_s_004c47e7,&DAT_005594b4,local_21c,&DAT_005595b8);
      }
      FUN_004a6b48(&DAT_005595bd,local_118,0x104);
      FUN_004893b4(local_118,local_21c);
      FUN_0049eb44(DAT_004c4788,0xf,1,0xf,0,local_21c);
      uVar3 = 1;
    }
  }
  return uVar3;
}

