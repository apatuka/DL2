// FUN_0043e22c @ 0043e22c size=274 sig=undefined FUN_0043e22c() cc=unknown
// callers: CheckViewCombat,FUN_00449084
// callees: FUN_0049a9e7,GetWindowLongA,FUN_0043e198,FUN_004a5edf,FUN_0048c85e,FUN_004a5ebb,FUN_004a2078,FUN_004a5ad9,InvalidateRect,FUN_004a5b30,FUN_004a5ece,FUN_0048c434,FUN_0049a8ed,FUN_0049a93f

void FUN_0043e22c(void)

{
  undefined4 uVar1;
  LONG LVar2;
  int iVar3;
  int iVar4;
  RECT local_1c;
  
  if (DAT_004c4950 != 0) {
    LVar2 = GetWindowLongA(DAT_004d5974,0xc);
    uVar1 = DAT_0051bddc;
    if (LVar2 != 0) {
      FUN_0048c434(*(undefined4 *)(&DAT_0058de34 + LVar2 * 0x1c));
      *(undefined4 *)(DAT_004c4950 + 0x3c) = *(undefined4 *)(&DAT_0058de34 + LVar2 * 0x1c);
      FUN_004a5b30();
      iVar3 = FUN_004a5ece(0);
      if (iVar3 != 0) {
        FUN_0049a8ed();
        while (iVar4 = iVar3 + -1, iVar3 != 0) {
          FUN_004a5edf(iVar4,0,&local_1c);
          FUN_0049a9e7(&local_1c);
          FUN_0043e198();
          FUN_004a2078(DAT_004c4950);
          FUN_004a5ad9();
          iVar3 = iVar4;
          if (((DAT_004c4950 == 0) || (*(int *)(DAT_004c4950 + 0x3c) == 0)) ||
             ((*(byte *)(DAT_004c4950 + 0x1c) & 2) == 0)) {
            if (*(int *)(DAT_004c4950 + 0x24) != 0) {
              InvalidateRect(*(HWND *)(DAT_004c4950 + 0x24),&local_1c,1);
            }
          }
          else {
            FUN_0048c85e(*(undefined4 *)(DAT_004c4950 + 0x3c),&DAT_0065e644,&local_1c,&local_1c,0,
                         &DAT_0065e580,0);
          }
        }
        FUN_0049a93f();
      }
      FUN_004a5ebb(0);
      FUN_0048c434(uVar1);
    }
  }
  return;
}

