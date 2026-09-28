// FUN_004158d0 @ 004158d0 size=29 sig=undefined FUN_004158d0() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_00415624,FUN_004155b0,FUN_00415830,FUN_0041585c

void FUN_004158d0(void)

{
  int iVar1;
  
  iVar1 = FUN_00415624();
  if (iVar1 != 0) {
    FUN_004155b0();
    do {
      iVar1 = FUN_0041585c();
    } while (iVar1 == 0);
    FUN_00415830();
  }
  return;
}

