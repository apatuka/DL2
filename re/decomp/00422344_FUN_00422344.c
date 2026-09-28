// FUN_00422344 @ 00422344 size=679 sig=undefined FUN_00422344() cc=unknown
// callers: FUN_00422bd8,FUN_00423104,FUN_00449084,FUN_00422f7c
// callees: FUN_004a5ece,FUN_004a5ad9,FUN_0049a93f,InvalidateRect,FUN_0048c85e,FUN_004a5ebb,FUN_00412d38,FUN_004a2078,FUN_0048c434,FUN_004a5edf,FUN_0049a8ed,FUN_004a5b30,FUN_0049a9e7

void FUN_00422344(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  RECT local_28;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  uVar1 = DAT_0051bddc;
  if (DAT_004b7b50 != 0) {
    FUN_0048c434(*(undefined4 *)(DAT_004b7b50 + 0x3c));
    FUN_004a5b30();
    iVar2 = FUN_004a5ece(0);
    if (iVar2 != 0) {
      FUN_0049a8ed();
      while (iVar3 = iVar2 + -1, iVar2 != 0) {
        FUN_004a5edf(iVar3,0,&local_28);
        FUN_0049a9e7(&local_28);
        FUN_004a2078(DAT_004b7b50);
        FUN_004a5ad9();
        if (((DAT_004b7b60 == 0) && (DAT_004b7b58 != 0)) && (*(char *)(DAT_004b7b58 + 0x3c) == '\0')
           ) {
          FUN_00412d38(DAT_004b7b58,*(undefined4 *)(DAT_004b7b50 + 0x3c));
        }
        iVar2 = iVar3;
        if (((DAT_004b7b50 == 0) || (*(int *)(DAT_004b7b50 + 0x3c) == 0)) ||
           ((*(byte *)(DAT_004b7b50 + 0x1c) & 2) == 0)) {
          if (*(int *)(DAT_004b7b50 + 0x24) != 0) {
            InvalidateRect(*(HWND *)(DAT_004b7b50 + 0x24),&local_28,1);
          }
        }
        else if (DAT_004c5b74 == 0) {
          FUN_0048c85e(*(undefined4 *)(DAT_004b7b50 + 0x3c),&DAT_0065e644,&local_28,&local_28,0,
                       &DAT_0065e580,0);
        }
        else {
          if (local_28.top < DAT_004c5b74) {
            local_14 = local_28.top;
            local_c = DAT_004c5b74 + -1;
            local_18 = local_28.left;
            local_10 = local_28.right;
            FUN_0048c85e(*(undefined4 *)(DAT_004b7b50 + 0x3c),&DAT_0065e644,&local_18,&local_18,0,
                         &DAT_0065e580,0);
          }
          if (DAT_004c5b7c < local_28.bottom) {
            local_14 = DAT_004c5b7c + 1;
            local_c = local_28.bottom;
            local_18 = local_28.left;
            local_10 = local_28.right;
            FUN_0048c85e(*(undefined4 *)(DAT_004b7b50 + 0x3c),&DAT_0065e644,&local_18,&local_18,0,
                         &DAT_0065e580,0);
          }
          if (local_28.left < DAT_004c5b70) {
            local_18 = local_28.left;
            local_10 = DAT_004c5b70 + -1;
            local_14 = local_28.top;
            if (local_28.top < DAT_004c5b74) {
              local_14 = DAT_004c5b74;
            }
            local_c = DAT_004c5b7c;
            if (local_28.bottom < DAT_004c5b7c) {
              local_c = local_28.bottom;
            }
            FUN_0048c85e(*(undefined4 *)(DAT_004b7b50 + 0x3c),&DAT_0065e644,&local_18,&local_18,0,
                         &DAT_0065e580,0);
          }
          if (DAT_004c5b78 < local_28.right) {
            local_18 = DAT_004c5b78 + 1;
            local_10 = local_28.right;
            local_14 = local_28.top;
            if (local_28.top < DAT_004c5b74) {
              local_14 = DAT_004c5b74;
            }
            local_c = DAT_004c5b7c;
            if (local_28.bottom < DAT_004c5b7c) {
              local_c = local_28.bottom;
            }
            FUN_0048c85e(*(undefined4 *)(DAT_004b7b50 + 0x3c),&DAT_0065e644,&local_18,&local_18,0,
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

