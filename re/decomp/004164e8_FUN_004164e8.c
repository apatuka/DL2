// FUN_004164e8 @ 004164e8 size=47 sig=undefined FUN_004164e8() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_00416448,FUN_004163d4,FUN_00416474,FUN_004158f0,FUN_004748dc

void FUN_004164e8(void)

{
  int iVar1;
  
  if ((DAT_004d5aa0 != '\0') && (iVar1 = FUN_004748dc(), iVar1 != 0)) {
    return;
  }
  iVar1 = FUN_004163d4();
  if (iVar1 != 0) {
    FUN_004158f0();
    do {
      iVar1 = FUN_00416474();
    } while (iVar1 == 0);
    FUN_00416448();
  }
  return;
}

