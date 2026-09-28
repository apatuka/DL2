// FUN_0040c21c @ 0040c21c size=65 sig=undefined FUN_0040c21c() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040c018,FUN_0040c1b0,FUN_0040e6e4

void FUN_0040c21c(int param_1)

{
  int iVar1;
  
  FUN_0040c018(param_1);
  iVar1 = 0;
  do {
    FUN_0040e6e4(&DAT_00522584 + param_1 * 0x2648 + iVar1 * 0xc4);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x32);
  FUN_0040c1b0(param_1);
  return;
}

