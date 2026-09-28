// FUN_00449dec @ 00449dec size=358 sig=undefined FUN_00449dec() cc=unknown
// callers: FUN_00414004,FUN_0043bd5c,FUN_0045c560,FUN_0043bdf4,FUN_00419924,FUN_0045b304,FUN_0045c704,FUN_00438b14,RunAITurns,FUN_0045e794,FUN_0045ca3c,FUN_004730a8,FUN_0044a5e8,FUN_0045b094,FUN_00431e58,FUN_0045d418,FUN_00458b54,FUN_00481098,FUN_0045e398,FUN_0045d984,FUN_00473e9c,FUN_004732d0,FUN_0045b8e8,FUN_0045b448,FUN_0043be98,FUN_0045d6a4,FUN_0043be24,FUN_0045c384,FUN_0044a48c,FUN_00436000,FUN_0045dfd4,FUN_00430abc,FUN_0045eadc
// callees: FUN_00458c6c,FUN_0045a91c,FUN_00458ed8,FUN_0041ff24,FUN_00480150,InvalidateRect,FUN_00480d78,FUN_00449db4,FUN_004879fc,FUN_0048d2e7,FUN_00418e00,FUN_00440b68,FUN_0048d32c

void FUN_00449dec(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  RECT *pRVar4;
  RECT local_18;
  
  FUN_00458c6c();
  FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
  if (DAT_004d59b4 == 0) {
LAB_00449e36:
    FUN_00449db4();
    if (DAT_004d5ad0 == 0) {
      FUN_0045a91c();
    }
    else {
      FUN_00440b68();
    }
  }
  else {
    if (DAT_004d59b4 == 0x22) {
      cVar1 = FUN_00418e00();
      if ((cVar1 != '\0') && (DAT_005332b0 == '\0')) goto LAB_00449e36;
    }
    if (DAT_004d59b4 == 2) {
      FUN_00449db4();
      FUN_00480150();
    }
    else {
      if (DAT_004d59b4 != 1) {
        if ((DAT_004d59b4 != 0x22) || (DAT_005332b0 != '\0')) goto LAB_00449e9e;
        cVar1 = FUN_00418e00();
        if (cVar1 != '\0') goto LAB_00449e9e;
      }
      FUN_00480d78();
      FUN_00449db4();
      FUN_00480150();
    }
  }
LAB_00449e9e:
  if (((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) ||
     ((DAT_004d59b4 == 0x22 && (DAT_005332b0 == '\0')))) {
    FUN_00458ed8();
    FUN_00449db4();
    puVar3 = &DAT_004c5b98;
    pRVar4 = &local_18;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      pRVar4->left = *puVar3;
      puVar3 = puVar3 + 1;
      pRVar4 = (RECT *)((int)pRVar4 + 4);
    }
    local_18.left = DAT_004c5458;
    local_18.right = (DAT_004c5458 + DAT_004c5460) - DAT_004c5b60;
    local_18.top = DAT_004c545c;
    local_18.bottom = (DAT_004c545c + DAT_004c5464) - DAT_004c5b64;
    InvalidateRect(DAT_004d5974,&local_18,0);
    FUN_004879fc();
  }
  else if (((DAT_004d59b4 == 5) || (DAT_004d59b4 == 0x22)) || (DAT_004d59b4 == 7)) {
    FUN_00458ed8();
    FUN_0041ff24();
  }
  FUN_0048d32c();
  return;
}

