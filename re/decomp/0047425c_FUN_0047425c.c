// FUN_0047425c @ 0047425c size=369 sig=undefined FUN_0047425c() cc=unknown
// callers: @EditTileResourcesDialog$qqspvuiuil
// callees: FUN_004743d0,SendDlgItemMessageA,CheckDlgButton,sprintf,SetWindowTextA
// strings: \"Edit Resources (base terrain is %s)\"|\"Clear\"|\"Rough\"

void FUN_0047425c(HWND param_1)

{
  WPARAM WVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined **local_c;
  
  uVar4 = (int)*(short *)(DAT_006534c0 + 2) & 0xff;
  if (uVar4 == 0xff) {
    uVar4 = 6;
  }
  sprintf(&DAT_006534c6,PTR_s_Edit_Resources__base_terrain_is___00509d48,
          (&PTR_DAT_00509054)[*(char *)(DAT_00657de0 + 0x21)]);
  SetWindowTextA(param_1,&DAT_006534c6);
  DAT_00653498 = *(undefined2 *)(DAT_006534c0 + 8);
  DAT_0065349a = *(undefined2 *)(DAT_006534c0 + 10);
  DAT_0065349c = *(undefined2 *)(DAT_006534c0 + 6);
  DAT_0065349e = *(undefined2 *)(DAT_006534c0 + 0xc);
  DAT_006534a0 = *(undefined2 *)(DAT_006534c0 + 0xe);
  DAT_006534c4 = *(undefined1 *)(DAT_006534c0 + 4);
  DAT_006534a2 = *(undefined2 *)(DAT_006534c0 + 2);
  uVar2 = 0;
  local_c = &PTR_s_Clear_00509134;
  do {
    WVar1 = SendDlgItemMessageA(param_1,0x12e,0x180,0,(LPARAM)*local_c);
    SendDlgItemMessageA(param_1,0x12e,0x19a,WVar1,uVar2);
    if (uVar4 == uVar2) {
      SendDlgItemMessageA(param_1,0x12e,0x186,WVar1,0);
    }
    uVar2 = uVar2 + 1;
    local_c = local_c + 1;
  } while ((int)uVar2 < 7);
  WVar1 = 0;
  do {
    uVar2 = SendDlgItemMessageA(param_1,0x12e,0x199,WVar1,0);
    if (uVar4 == uVar2) {
      SendDlgItemMessageA(param_1,0x12e,0x186,WVar1,0);
      break;
    }
    WVar1 = WVar1 + 1;
  } while ((int)WVar1 < 7);
  if (*(char *)(DAT_006534c0 + 4) != '\0') {
    CheckDlgButton(param_1,0x12d,1);
  }
  iVar3 = 0;
  do {
    FUN_004743d0(param_1,iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 5);
  DAT_006534c5 = 0;
  return;
}

