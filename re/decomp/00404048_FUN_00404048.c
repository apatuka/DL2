// FUN_00404048 @ 00404048 size=923 sig=undefined FUN_00404048() cc=unknown
// callers: @DebugMinisterDialog$qqspvuiuil,FUN_004043e4
// callees: FUN_004a68dc,sprintf,FUN_00471c1c,SetDlgItemInt,SetDlgItemTextA
// strings: \"%d/%d\\n%d/%d\\n%d/%d\\n%d/%d\\n%d/%d\\n%d/%d\\n%d/%d\\n%d/%d\\n\"|\"%s: %s\"|\"Wars: \"|\"%d\\n%d\\n%d\\n\\n%d\\n%d\\n%d\\n%d\\n\"|\"%d/%d\"

void FUN_00404048(HWND param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined1 local_454 [4];
  undefined4 local_450;
  undefined4 local_44c;
  undefined4 local_448;
  undefined4 local_444;
  undefined4 local_434;
  undefined4 local_430;
  undefined4 local_42c;
  CHAR local_424 [1024];
  undefined4 *local_24;
  undefined4 *local_20;
  char *local_1c;
  uint *local_18;
  uint *local_14;
  char *local_10;
  int local_c;
  int local_8;
  
  local_8 = DAT_004b5380;
  local_c = 0;
  local_14 = (uint *)(&DAT_0052222c + DAT_004b5380 * 4);
  local_10 = &DAT_0059f162 + DAT_004b5380 * 0x2d8;
  do {
    iVar1 = local_8 * 0x2d8 + local_c * 0x5a;
    sprintf(local_424,&DAT_004b5390,(int)*(short *)(&DAT_0059f1d0 + iVar1),
            (int)*(short *)(&DAT_0059f1e8 + iVar1),(int)*(short *)(iVar1 + 0x59f204),
            *(undefined4 *)(&DAT_004f9dbc + *(short *)(iVar1 + 0x59f206) * 0x32));
    SetDlgItemTextA(param_1,local_c + 0x26,local_424);
    sprintf(local_424,s__d__d__d__d__d__d__d__d__d__d__d_004b539c,
            (int)*(short *)(&DAT_0059f1d2 + iVar1),(int)*(short *)(&DAT_0059f1ea + iVar1),
            (int)*(short *)(iVar1 + 0x59f1d6),(int)*(short *)(iVar1 + 0x59f1ee),
            (int)*(short *)(iVar1 + 0x59f1d4),(int)*(short *)(iVar1 + 0x59f1ec),
            (int)*(short *)(iVar1 + 0x59f200),(int)*(short *)(iVar1 + 0x59f1fe),
            (int)*(short *)(iVar1 + 0x59f1d8),(int)*(short *)(iVar1 + 0x59f1f0),
            (int)*(short *)(iVar1 + 0x59f1e2),(int)*(short *)(iVar1 + 0x59f1fa),
            (int)*(short *)(iVar1 + 0x59f1e0),(int)*(short *)(iVar1 + 0x59f1f8),
            (int)*(short *)(iVar1 + 0x59f1e4),(int)*(short *)(iVar1 + 0x59f1fc));
    SetDlgItemTextA(param_1,local_c + 0x3d,local_424);
    sprintf(local_424,s__s___s_004b53cd,(&PTR_s_ChCh_t_00509038)[*local_10],
            *(undefined4 *)(local_10 + 0x44));
    SetDlgItemTextA(param_1,0xe,local_424);
    sprintf(local_424,s_Wars__004b53d4);
    if (*local_14 == 0) {
      FUN_004a68dc(local_424,&DAT_004b53db);
    }
    else {
      local_1c = &DAT_0059f162;
      iVar2 = 0;
      local_18 = local_14;
      do {
        if ((1 << ((byte)iVar2 & 0x1f) & *local_18) != 0) {
          FUN_004a68dc(local_424,(&PTR_s_ChCh_t_00509038)[*local_1c]);
          FUN_004a68dc(local_424,s_Wars__004b53d4 + 5);
        }
        iVar2 = iVar2 + 1;
        local_1c = local_1c + 0x2d8;
      } while (iVar2 < 7);
    }
    SetDlgItemTextA(param_1,5,local_424);
    SetDlgItemInt(param_1,local_c + 0x32,(int)(char)(&DAT_0059f1bf)[iVar1],0);
    local_c = local_c + 1;
  } while (local_c < 6);
  FUN_00471c1c(local_8,local_454);
  sprintf(local_424,s__d__d__d__d__d__d__d__d__d__d__d_004b539c + 0x2a,DAT_00522018,
          (&DAT_0059f16c)[local_8 * 0xb6]);
  SetDlgItemTextA(param_1,0x2c,local_424);
  sprintf(local_424,s__d__d__d__d__d__d__d_004b53e0,local_450,local_448,local_44c,local_444,
          local_430,local_434,local_42c);
  SetDlgItemTextA(param_1,0x43,local_424);
  SetDlgItemInt(param_1,0x38,*(UINT *)(local_8 * 4 + 0x4b5124),0);
  pcVar3 = &DAT_0059f162;
  local_24 = (undefined4 *)(&DAT_00522168 + local_8 * 0x1c);
  local_20 = (undefined4 *)(&DAT_005220a4 + local_8 * 0x1c);
  for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
    sprintf(local_424,&DAT_004b5399,(&PTR_s_ChCh_t_00509038)[*pcVar3]);
    SetDlgItemTextA(param_1,iVar1 + 0x46,local_424);
    sprintf(local_424,s__d__d_004b53f7,*local_20,*local_24);
    SetDlgItemTextA(param_1,iVar1 + 0x50,local_424);
    local_24 = local_24 + 1;
    local_20 = local_20 + 1;
    pcVar3 = pcVar3 + 0x2d8;
  }
  return;
}

