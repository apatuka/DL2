// FUN_00421878 @ 00421878 size=43 sig=undefined FUN_00421878() cc=unknown
// callers: FUN_0043baf4
// callees: FUN_00420aac,FUN_004217f4

undefined4 FUN_00421878(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = DAT_004c5b50 * 0xadc;
  uVar2 = 0;
  cVar1 = FUN_004217f4(&DAT_005a43d0 + iVar3);
  if (cVar1 != '\0') {
    uVar2 = FUN_00420aac(&DAT_005a43d0 + iVar3);
  }
  return uVar2;
}

