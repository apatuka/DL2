// FUN_00462348 @ 00462348 size=52 sig=undefined FUN_00462348() cc=unknown
// callers: FUN_004632f4,FUN_00469b2c,FUN_004634a0,FUN_00469744,FUN_004694c0,FUN_00463014,FUN_0046a020,FUN_00462994
// callees: MessagePump,FUN_0041e81c

undefined4 FUN_00462348(void)

{
  int iVar1;
  
  if (DAT_0058f1ec == 0) {
    MessagePump();
    iVar1 = FUN_0041e81c();
    if (iVar1 == 5) {
      DAT_0058f1ec = 1;
    }
  }
  if (DAT_0058f1ec != 0) {
    return 1;
  }
  return 0;
}

