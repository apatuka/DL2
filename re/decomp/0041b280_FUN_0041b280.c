// FUN_0041b280 @ 0041b280 size=94 sig=undefined FUN_0041b280() cc=unknown
// callers: FUN_0045ef64
// callees: CheckBuildingList,FUN_0041ac34,FUN_0048e11b,FUN_004748dc,FUN_0041b1c8

undefined4 FUN_0041b280(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((DAT_004d5aa0 != '\0') && (iVar1 = FUN_004748dc(), iVar1 != 0)) {
    return 0;
  }
  DAT_0053b334 = param_1;
  iVar1 = FUN_0041b1c8();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_0041ac34();
    iVar1 = 0;
    while ((iVar1 != 3 && (iVar1 != 4))) {
      iVar1 = CheckBuildingList();
    }
    if (iVar1 == 3) {
      FUN_0048e11b();
      uVar2 = DAT_004b76fc;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

