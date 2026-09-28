// FUN_004879b0 @ 004879b0 size=69 sig=undefined FUN_004879b0() cc=unknown
// callers: FUN_00472e04,FUN_00488074,FUN_004694c0,FUN_00469b2c,FUN_004634a0,FUN_0046a020,FUN_00469744
// callees: FUN_004878a8

void FUN_004879b0(void)

{
  int iVar1;
  
  if ((((DAT_005126dc != 0) && (DAT_005126dc != 0)) && ((*(byte *)(DAT_005126dc + 0x28) & 1) != 0))
     && ((*(byte *)(DAT_005126dc + 0xb4) & 1) != 0)) {
    iVar1 = (**(code **)(*(int *)(DAT_005126dc + 0xb8) + 0x7c))(*(int *)(DAT_005126dc + 0xb8));
    if ((iVar1 == 0) && (DAT_0065e548 != 0)) {
      FUN_004878a8();
    }
  }
  return;
}

