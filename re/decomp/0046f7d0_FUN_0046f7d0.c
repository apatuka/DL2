// FUN_0046f7d0 @ 0046f7d0 size=49 sig=undefined FUN_0046f7d0() cc=unknown
// callers: FUN_0046f804
// callees: 

undefined4 FUN_0046f7d0(void)

{
  undefined2 *puVar1;
  
  puVar1 = &DAT_005f0410;
  while( true ) {
    if ((undefined2 *)0x64536f < puVar1) {
      return 0;
    }
    if ((*(char *)((int)puVar1 + 5) == '\x05') && ((puVar1[1] & 6) == 6)) break;
    puVar1 = puVar1 + 0x91;
  }
  return 1;
}

