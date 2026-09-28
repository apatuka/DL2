// FUN_00414f38 @ 00414f38 size=581 sig=undefined FUN_00414f38() cc=unknown
// callers: FUN_0042e694,FUN_004155b0,FUN_00418cf4,FUN_0042ed64,FUN_0042c1a4,FUN_0041e674,FUN_00436064,FUN_0042f554,FUN_0043a5b8,FUN_00436418,FUN_00426808,FUN_00438ef8,FUN_00414914,FUN_0042e3e4,FUN_00427c40,FUN_004218a4,FUN_0042726c,FUN_00423dd8,FUN_00424474,FUN_00414a30,FUN_00413c70,FUN_0041ff18,FUN_0042d04c,FUN_004144a8,FUN_0043ba98,FUN_00432cdc,FUN_0041ac34,FUN_00423bf0,FUN_0042ea8c,FUN_00432cd0,FUN_004302e8,FUN_004167b0,FUN_0042dee0,FUN_00432cc4,FUN_0043997c,FUN_00424eb4,FUN_0042ba98,FUN_0041f354,FUN_00432ce8,FUN_00427f4c,FUN_00438214,FUN_00416518,FUN_004133cc,FUN_00425ef8,UserMessageObject__CheckMessage,FUN_00436184,FUN_0041c36c,FUN_004158f0,FUN_004371e4,FUN_00428860,FUN_0042a2c4,FUN_00428408,FUN_00436d84,FUN_0043c988,FUN_0043a33c,FUN_004152f8
// callees: FUN_0048c85e,FUN_004a5edf,FUN_0049a9e7,FUN_0049a8ed,InvalidateRect,FUN_004a421e,FUN_0048c434,FUN_004a5ebb,FUN_004a5ece,FUN_004a5b30,FUN_004a5ad9,FUN_0049a93f,FUN_004879fc

void FUN_00414f38(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  RECT local_14;
  
  uVar1 = DAT_0051bddc;
  DAT_0053328c = 0;
  if (param_1 != 0) {
    FUN_0048c434(*(undefined4 *)(param_1 + 0x3c));
    FUN_004a5b30();
    iVar2 = FUN_004a5ece(0);
    if (iVar2 != 0) {
      FUN_0049a8ed();
      while (iVar3 = iVar2 + -1, iVar2 != 0) {
        FUN_004a5edf(iVar3,0,&local_14);
        FUN_0049a9e7(&local_14);
        FUN_004a421e(0);
        FUN_004a5ad9();
        FUN_004879fc();
        iVar2 = iVar3;
        if (((param_1 == 0) || (*(int *)(param_1 + 0x3c) == 0)) ||
           ((*(byte *)(param_1 + 0x1c) & 2) == 0)) {
          if (*(int *)(param_1 + 0x24) != 0) {
            InvalidateRect(*(HWND *)(param_1 + 0x24),&local_14,1);
          }
        }
        else if (DAT_004c5b74 == 0) {
          FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,&local_14,&local_14,0,
                       &DAT_0065e580,0);
        }
        else {
          if (local_14.top < DAT_004c5b74) {
            local_20 = local_14.top;
            local_18 = DAT_004c5b74 + -1;
            local_24 = local_14.left;
            local_1c = local_14.right;
            FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,&local_24,&local_24,0,
                         &DAT_0065e580,0);
          }
          if (DAT_004c5b7c < local_14.bottom) {
            local_20 = DAT_004c5b7c + 1;
            local_18 = local_14.bottom;
            local_24 = local_14.left;
            local_1c = local_14.right;
            FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,&local_24,&local_24,0,
                         &DAT_0065e580,0);
          }
          if (local_14.left < DAT_004c5b70) {
            local_24 = local_14.left;
            local_1c = DAT_004c5b70 + -1;
            local_20 = local_14.top;
            if (local_14.top < DAT_004c5b74) {
              local_20 = DAT_004c5b74;
            }
            local_18 = DAT_004c5b7c;
            if (local_14.bottom < DAT_004c5b7c) {
              local_18 = local_14.bottom;
            }
            FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,&local_24,&local_24,0,
                         &DAT_0065e580,0);
          }
          if (DAT_004c5b78 < local_14.right) {
            local_24 = DAT_004c5b78 + 1;
            local_1c = local_14.right;
            local_20 = local_14.top;
            if (local_14.top < DAT_004c5b74) {
              local_20 = DAT_004c5b74;
            }
            local_18 = DAT_004c5b7c;
            if (local_14.bottom < DAT_004c5b7c) {
              local_18 = local_14.bottom;
            }
            FUN_0048c85e(*(undefined4 *)(param_1 + 0x3c),&DAT_0065e644,&local_24,&local_24,0,
                         &DAT_0065e580,0);
          }
        }
      }
      FUN_0049a93f();
    }
    FUN_004a5ebb(0);
    FUN_0048c434(uVar1);
  }
  return;
}

