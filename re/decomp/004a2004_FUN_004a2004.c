// FUN_004a2004 @ 004a2004 size=116 sig=undefined FUN_004a2004() cc=unknown
// callers: FUN_00414508,FUN_00436db8,FUN_0042ee18,FUN_00423e38,FUN_00419710,FUN_00432ad0,FUN_0042d0ac,FUN_0042e434,FUN_00425f58,FUN_00415624,FUN_0042a36c,FUN_0041b1c8,FUN_0043a394,FUN_004a5c60,FUN_00421904,FUN_004272f8,FUN_0043e590,FUN_00415484,FUN_00416810,FUN_00423104,FUN_00423c24,FUN_0042e6f4,FUN_004197dc,FUN_0042df6c,FUN_0042baf8,FUN_0041f384,FUN_00438fe0,FUN_004a3329,FUN_0042f680,FUN_004163d4,FUN_004288c0,FUN_00434f28,FUN_00430348,FUN_00416578,FUN_00427ca0,FUN_00413cd0,FUN_0041ccb0,FUN_0042eaec,FUN_00426868,FUN_00436098,FUN_00420aac,FUN_004399dc,FUN_0043735c,FUN_00438830,FUN_0041e6d4,FUN_004244d4,FUN_0043644c,FUN_0042c204,FUN_00413694,FUN_004361b8,FUN_0043242c,FUN_00424f14,FUN_0043c260,FUN_00428468,FUN_00414958,FUN_004197a8,FUN_00427fe0,FUN_0043ca24,FUN_0043210c
// callees: FUN_004a1fc4,FUN_0049f83e,FUN_0049e638

void FUN_004a2004(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 8) == -1) {
    if (*(int *)(param_1 + 0x3c) == 0) {
      iVar2 = *(int *)(DAT_0051bddc + 4);
    }
    else {
      iVar2 = *(int *)(*(int *)(param_1 + 0x3c) + 4);
    }
    uVar1 = iVar2 - *(int *)(param_1 + 0x14);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    *(int *)(param_1 + 8) = iVar2;
  }
  if (*(int *)(param_1 + 0xc) == -1) {
    if (*(int *)(param_1 + 0x3c) == 0) {
      iVar2 = *(int *)(DAT_0051bddc + 8);
    }
    else {
      iVar2 = *(int *)(*(int *)(param_1 + 0x3c) + 8);
    }
    uVar1 = iVar2 - *(int *)(param_1 + 0x10);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    *(int *)(param_1 + 0xc) = iVar2;
  }
  FUN_004a1fc4(param_1);
  FUN_0049f83e(param_1);
  FUN_0049e638(param_1,*(undefined4 *)(param_1 + 0x50));
  return;
}

