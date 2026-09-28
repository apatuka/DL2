// FUN_00486798 @ 00486798 size=64 sig=undefined FUN_00486798() cc=unknown
// callers: FUN_00480d78
// callees: FUN_00444f20,FUN_00486734

void FUN_00486798(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_0065e028 < 0x20) {
    iVar1 = FUN_00444f20(0x82,0,0,0);
    if (iVar1 != 0) {
      FUN_00486734(DAT_0065e028,iVar1,param_1);
      DAT_0065e028 = DAT_0065e028 + 1;
    }
  }
  return;
}

