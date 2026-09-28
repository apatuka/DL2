// FUN_00467fc0 @ 00467fc0 size=111 sig=undefined FUN_00467fc0() cc=unknown
// callers: 
// callees: FUN_004780e4,FUN_004618e8,FUN_00467e58,FUN_00416af0

undefined4 FUN_00467fc0(void)

{
  int iVar1;
  undefined1 local_108 [260];
  
  iVar1 = FUN_00416af0(0xff);
  if (iVar1 != -1) {
    FUN_00467e58(local_108,iVar1,1);
    FUN_004780e4(DAT_0058f1f4,1);
    iVar1 = FUN_004618e8(local_108,1);
    if (iVar1 != 0) {
      if (DAT_004d59b4 == 0x32) {
        DAT_004d59b4 = 0;
      }
      DAT_004d598c = 1;
      return 0x46;
    }
  }
  return 0x35;
}

