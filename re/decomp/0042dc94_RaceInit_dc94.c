// RaceInit_dc94 @ 0042dc94 size=468 sig=undefined RaceInit_dc94() cc=unknown
// callers: FUN_0042df6c
// callees: FUN_0046c9d8,FUN_0042d994,sprintf,memset,FUN_0042d660,FUN_0042d550,FUN_0046eda8,FUN_0042d47c,FUN_0049117e,FUN_0049eb44,FUN_0042e66c
// strings: \"RaceInit\"|\"Player #%d is selecting a race.\"|\"Select which race you will command.\"

/* auto-named from string evidence: RaceInit */

void RaceInit_dc94(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_100 [256];
  
  DAT_00557c80 = 0;
  FUN_0046eda8(s_RaceInit_004c3690);
  memset(&DAT_00557c54,0,0x1c);
  DAT_00557c70 = 0;
  if ((DAT_004d5a50 == 0) && (DAT_004d513c == 0)) {
    DAT_00557c7c = DAT_0058f1f4;
  }
  else if ((DAT_004d513c == 0) && (DAT_0058f1fc == 0)) {
    DAT_00557c7c = FUN_0046c9d8(DAT_004d5aec,s_RaceInit_004c3690);
  }
  else {
    DAT_00557c7c = 0;
  }
  DAT_00557c78 = DAT_00557c7c;
  FUN_0042d660();
  FUN_0042d994();
  if ((DAT_004d5aa0 == '\0') &&
     (DAT_004c366c = FUN_0046c9d8(7,s_RaceInit_004c3690), DAT_004d513c != 0)) {
    while ((1 << ((byte)DAT_004c366c & 0x1f) & (int)DAT_0058f12e) == 0) {
      DAT_004c366c = DAT_004c366c + 1;
      if (7 < DAT_004c366c) {
        DAT_004c366c = 0;
      }
    }
  }
  FUN_0042e66c(DAT_004c366c);
  uVar6 = 0;
  uVar5 = 1;
  uVar4 = 0xb;
  uVar3 = 1;
  uVar1 = FUN_0042d47c(DAT_004c366c);
  FUN_0049eb44(DAT_004c3668,uVar1,uVar3,uVar4,uVar5,uVar6);
  if (DAT_004d5aa0 == '\0') {
    (&DAT_005a0548)[DAT_0058f1f4] = 2;
    FUN_0049eb44(DAT_004c3668,(char)(&DAT_005a0548)[DAT_00557c7c] + 9,1,0xb,1,0);
    puVar2 = PTR_s_Select_which_race_you_will_comma_0050940c;
    if (DAT_00557c7c != DAT_0058f1f4) {
      sprintf(local_100,PTR_s_Player___d_is_selecting_a_race__00509410,DAT_00557c7c + 1);
      puVar2 = local_100;
    }
  }
  else if (DAT_00557c74 == 0) {
    puVar2 = (undefined *)FUN_0049117e(0,0x54494445,1);
  }
  else {
    puVar2 = (undefined *)FUN_0049117e(0,0x54494445,3);
  }
  FUN_0049eb44(DAT_004c3668,0x14,1,0xf,0,puVar2);
  FUN_0042d550();
  return;
}

