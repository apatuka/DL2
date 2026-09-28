// FUN_00414508 @ 00414508 size=801 sig=undefined FUN_00414508() cc=unknown
// callers: FUN_004148ec
// callees: FUN_00414f04,FUN_004a3de6,FUN_004a60b1,FUN_0049eb44,FUN_004a2004,FUN_004493dc,sprintf

bool FUN_00414508(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined1 local_84 [128];
  
  DAT_004b7054 = FUN_004a3de6(0,0x31323944);
  bVar3 = DAT_004b7054 != 0;
  if (bVar3) {
    FUN_004493dc(1);
    DAT_00533210 = DAT_004d59b4;
    DAT_004d59b4 = 0x58;
    FUN_00414f04(DAT_004b7054);
    local_94 = DAT_004b705c;
    local_90 = DAT_004b7058;
    local_8c = DAT_004b7064;
    local_88 = DAT_004b7060;
    FUN_004a60b1(&local_94,0);
    FUN_004a2004(DAT_004b7054);
    iVar1 = DAT_004c5b50;
    iVar2 = DAT_004c5b50 * 0xadc;
    sprintf(local_84,&DAT_004b7068,(&DAT_005a440e)[DAT_004c5b50 * 0x2b7]);
    FUN_0049eb44(DAT_004b7054,6,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,(&DAT_005a4412)[iVar1 * 0x2b7]);
    FUN_0049eb44(DAT_004b7054,8,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a4416 + iVar2));
    FUN_0049eb44(DAT_004b7054,10,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a441a + iVar2));
    FUN_0049eb44(DAT_004b7054,0xc,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a441e + iVar2));
    FUN_0049eb44(DAT_004b7054,0xe,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,(int)(short)(&DAT_005a4400)[iVar1 * 0x56e]);
    FUN_0049eb44(DAT_004b7054,0x10,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a4422 + iVar2));
    FUN_0049eb44(DAT_004b7054,0x12,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a4426 + iVar2));
    FUN_0049eb44(DAT_004b7054,0x14,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a442a + iVar2));
    FUN_0049eb44(DAT_004b7054,0x16,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a442e + iVar2));
    FUN_0049eb44(DAT_004b7054,0x18,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,*(undefined4 *)(&DAT_005a4432 + iVar2));
    FUN_0049eb44(DAT_004b7054,0x1a,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
    FUN_0049eb44(DAT_004b7054,0x1c,1,0xf,0,local_84);
    sprintf(local_84,&DAT_004b7068,(int)(char)(&DAT_005a43f7)[iVar2]);
    FUN_0049eb44(DAT_004b7054,0x1e,1,0xf,0,local_84);
  }
  return bVar3;
}

