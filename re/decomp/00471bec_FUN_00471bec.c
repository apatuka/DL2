// FUN_00471bec @ 00471bec size=47 sig=undefined FUN_00471bec() cc=unknown
// callers: FUN_0046c7d4,FUN_004720f4,FUN_00472ca0
// callees: memset

void FUN_00471bec(void)

{
  int iVar1;
  
  for (iVar1 = 1; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
    memset(&DAT_005a4e4e + iVar1 * 0xadc,0,0x2c);
  }
  return;
}

