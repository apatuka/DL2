// FUN_00468030 @ 00468030 size=124 sig=undefined FUN_00468030() cc=unknown
// callers: FUN_0045e7a4
// callees: FUN_004780e4,FUN_004618e8,FUN_00467e58

void FUN_00468030(void)

{
  int iVar1;
  int iVar2;
  undefined1 local_108 [260];
  
  iVar2 = DAT_004d5a94 % 6;
  iVar1 = DAT_004d5a94 / 6;
  if (iVar2 == 0) {
    iVar2 = 6;
    iVar1 = iVar1 + -1;
  }
  FUN_00467e58(local_108,iVar1,iVar2);
  FUN_004780e4(DAT_0058f1f4,1);
  iVar1 = FUN_004618e8(local_108,1);
  if (iVar1 != 0) {
    if (DAT_004d59b4 == 0x32) {
      DAT_004d59b4 = 0;
    }
    DAT_004d598c = 1;
  }
  return;
}

