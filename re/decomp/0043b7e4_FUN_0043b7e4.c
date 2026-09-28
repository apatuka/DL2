// FUN_0043b7e4 @ 0043b7e4 size=87 sig=undefined FUN_0043b7e4() cc=unknown
// callers: FUN_00449fd8,FUN_0043be98,FUN_0043b83c,FUN_0043baa4,DisableMainInterface,FUN_0043baf4
// callees: FUN_0049eb44,FUN_0043b754

void FUN_0043b7e4(void)

{
  int iVar1;
  
  if (DAT_004d5aa0 == '\0') {
    iVar1 = 1000;
    do {
      FUN_0049eb44(DAT_004c48a0,iVar1,1,8,0,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x3f2);
  }
  else {
    iVar1 = 1000;
    do {
      FUN_0049eb44(DAT_004c48a0,iVar1,1,8,0,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x3f2);
  }
  FUN_0043b754();
  return;
}

