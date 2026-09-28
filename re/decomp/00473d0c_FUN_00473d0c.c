// FUN_00473d0c @ 00473d0c size=397 sig=undefined FUN_00473d0c() cc=unknown
// callers: @EditTerritoryResourcesDialog$qqspvuiuil
// callees: SetDlgItemInt,sprintf,SetWindowTextA
// strings: \"Territory '%s'\"

void FUN_00473d0c(HWND param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_004c5b50;
  iVar2 = DAT_004c5b50 * 0xadc;
  sprintf(&DAT_006534c6,PTR_s_Territory___s__00509d44,&DAT_005a43d0 + iVar2);
  SetWindowTextA(param_1,&DAT_006534c6);
  DAT_006534a4 = (UINT)(short)(&DAT_005a4400)[iVar1 * 0x56e];
  DAT_006534a8 = *(UINT *)(PTR_DAT_004d5988 + 0xc);
  DAT_00653498 = *(short *)(&DAT_005a440e + iVar1 * 0x2b7);
  DAT_0065349c = *(short *)(&DAT_005a4412 + iVar1 * 0x2b7);
  DAT_0065349a = *(short *)(&DAT_005a4416 + iVar2);
  DAT_0065349e = *(short *)(&DAT_005a441a + iVar2);
  DAT_006534ac = (UINT)*(short *)(&DAT_005a441e + iVar2);
  DAT_006534a0 = *(short *)(&DAT_005a4422 + iVar2);
  DAT_006534b0 = (UINT)*(short *)(&DAT_005a4426 + iVar2);
  DAT_006534b4 = (UINT)*(short *)(&DAT_005a442a + iVar2);
  DAT_006534b8 = (UINT)*(short *)(&DAT_005a442e + iVar2);
  DAT_006534bc = (UINT)*(short *)(&DAT_005a4432 + iVar2);
  SetDlgItemInt(param_1,100,DAT_006534a4,0);
  SetDlgItemInt(param_1,0x65,DAT_006534a8,0);
  SetDlgItemInt(param_1,0x66,(int)DAT_00653498,0);
  SetDlgItemInt(param_1,0x67,(int)DAT_0065349c,0);
  SetDlgItemInt(param_1,0x68,(int)DAT_0065349a,0);
  SetDlgItemInt(param_1,0x69,(int)DAT_0065349e,0);
  SetDlgItemInt(param_1,0x6a,DAT_006534ac,0);
  SetDlgItemInt(param_1,0x6b,(int)DAT_006534a0,0);
  SetDlgItemInt(param_1,0x6c,DAT_006534b0,0);
  SetDlgItemInt(param_1,0x6d,DAT_006534b4,0);
  SetDlgItemInt(param_1,0x6e,DAT_006534b8,0);
  SetDlgItemInt(param_1,0x6f,DAT_006534bc,0);
  DAT_006534c5 = 0;
  return;
}

