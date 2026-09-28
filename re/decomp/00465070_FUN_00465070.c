// FUN_00465070 @ 00465070 size=241 sig=undefined FUN_00465070() cc=unknown
// callers: @TransferDialog$qqspvuiuil,@GameStyleDialog$qqspvuiuil
// callees: ReadDataFileChunk,FUN_00464b90,FUN_00464f80,SetBkMode,FUN_0046534c,memcpy,GetClientRect
// strings: \"SPRITENW.DAT\"

void FUN_00465070(HWND param_1,HDC param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined1 *puVar3;
  int *piVar4;
  undefined1 local_34 [4];
  int local_30;
  int local_28;
  tagRECT local_24;
  int local_14 [4];
  
  puVar3 = *(undefined1 **)(param_3 + 8);
  if (param_3 != 0) {
    if (puVar3 == (undefined1 *)0x0) {
      puVar3 = &DAT_00592d9c;
      ReadDataFileChunk(s_SPRITENW_DAT_004d2392,&DAT_00592d9c,*(undefined4 *)(param_3 + 0xc),
                        (int)*(short *)(param_3 + 4) * (int)*(short *)(param_3 + 6));
    }
    piVar2 = &DAT_004d2368;
    piVar4 = local_14;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar4 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar4 = piVar4 + 1;
    }
    local_14[2] = (int)*(short *)(param_3 + 4);
    local_14[3] = (int)*(short *)(param_3 + 6);
    FUN_00464b90(param_2,local_14,puVar3,local_14[2],local_14[3]);
    FUN_00464f80(param_2,local_14,1);
  }
  GetClientRect(param_1,&local_24);
  SetBkMode(param_2,1);
  memcpy(local_34,&local_24,0x10);
  local_24.left = (LONG)*(short *)(param_3 + 4);
  if (local_24.left < local_24.right) {
    FUN_0046534c(param_2,DAT_0058f1b4,&local_24,0x80,0x40);
  }
  local_30 = (int)*(short *)(param_3 + 6);
  if (local_30 < local_28) {
    FUN_0046534c(param_2,DAT_0058f1b4,local_34,0x80,0x40);
  }
  return;
}

