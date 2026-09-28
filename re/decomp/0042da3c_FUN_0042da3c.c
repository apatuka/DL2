// FUN_0042da3c @ 0042da3c size=378 sig=undefined FUN_0042da3c() cc=unknown
// callers: FUN_0042dbb8,FUN_0042e244
// callees: Sleep,FUN_0042deec,FUN_0042dee0,FUN_0042d994,SelRace,sprintf,FUN_0042d660,FUN_0042d550,FUN_0042d47c,UpdateWindow,FUN_0049eb44,FUN_0042e66c
// strings: \"Player #%d is selecting a race.\"|\"Select which race you will command.\"

void FUN_0042da3c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_104 [256];
  
  iVar1 = DAT_00557c7c;
  do {
    DAT_00557c7c = DAT_00557c7c + 1;
    if (DAT_004d5aec <= DAT_00557c7c) {
      DAT_00557c7c = 0;
    }
  } while ((&DAT_0059f161)[DAT_00557c7c * 0x2d8] == '\0');
  if (DAT_00557c7c == DAT_00557c78) {
    DAT_00557c80 = 1;
  }
  FUN_0042d660();
  FUN_0042d994();
  if ((DAT_00557c7c == DAT_0058f1f4) && (DAT_00557c7c != DAT_00557c78)) {
    if (DAT_004d5aa0 == '\0') {
      DAT_004c366c = SelRace();
    }
    uVar7 = 0;
    uVar6 = 1;
    uVar5 = 0xb;
    uVar4 = 1;
    uVar2 = FUN_0042d47c(DAT_004c366c);
    FUN_0049eb44(DAT_004c3668,uVar2,uVar4,uVar5,uVar6,uVar7);
  }
  FUN_0042e66c(DAT_004c366c);
  puVar3 = PTR_s_Select_which_race_you_will_comma_0050940c;
  if (DAT_00557c7c != DAT_0058f1f4) {
    sprintf(local_104,PTR_s_Player___d_is_selecting_a_race__00509410,DAT_00557c7c + 1);
    puVar3 = local_104;
  }
  FUN_0049eb44(DAT_004c3668,0x14,1,0xf,0,puVar3);
  FUN_0042d550();
  FUN_0042deec();
  FUN_0042dee0();
  UpdateWindow(DAT_004d5978);
  if ((char)(&DAT_0059f161)[iVar1 * 0x2d8] < '\x03' &&
      '\x02' < (char)(&DAT_0059f161)[DAT_00557c7c * 0x2d8]) {
    Sleep(1000);
  }
  return;
}

