// FUN_0046903c @ 0046903c size=54 sig=undefined FUN_0046903c() cc=unknown
// callers: FUN_00468214
// callees: FUN_0043a1f8,FUN_0043694c

int FUN_0046903c(void)

{
  int iVar1;
  
  iVar1 = FUN_0043694c(0x31);
  if (iVar1 == 6) {
    iVar1 = FUN_0043a1f8(5);
    if (iVar1 == 0x38) {
      return 0x3b;
    }
  }
  else {
    if (iVar1 == 8) {
      return 0x3b;
    }
    iVar1 = 0x35;
  }
  return iVar1;
}

