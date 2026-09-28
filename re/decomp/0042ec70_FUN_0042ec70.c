// FUN_0042ec70 @ 0042ec70 size=31 sig=undefined FUN_0042ec70() cc=unknown
// callers: 
// callees: FUN_0042eaec,FUN_0042ea8c,FUN_0042eb7c,FUN_0042ebb8

void FUN_0042ec70(void)

{
  int iVar1;
  
  iVar1 = FUN_0042eaec();
  if (iVar1 != 0) {
    FUN_0042ea8c();
    do {
      iVar1 = FUN_0042ebb8();
    } while (iVar1 == 0);
    FUN_0042eb7c();
  }
  return;
}

