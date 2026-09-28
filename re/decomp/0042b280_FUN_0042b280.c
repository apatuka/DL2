// FUN_0042b280 @ 0042b280 size=49 sig=undefined FUN_0042b280() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_0042a36c,FUN_0042a2c4,FUN_004748dc,FUN_0042ac68,FUN_0042ac2c

void FUN_0042b280(void)

{
  int iVar1;
  
  if ((DAT_004d5aa0 != '\0') && (iVar1 = FUN_004748dc(), iVar1 != 0)) {
    return;
  }
  iVar1 = FUN_0042a36c();
  if (iVar1 != 0) {
    FUN_0042a2c4();
    do {
      iVar1 = FUN_0042ac68();
    } while (iVar1 == 0);
    FUN_0042ac2c();
  }
  return;
}

