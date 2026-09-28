// FUN_0043ded0 @ 0043ded0 size=108 sig=undefined FUN_0043ded0() cc=unknown
// callers: FUN_0043e168,CheckViewCombat,FUN_0043e590
// callees: 

uint FUN_0043ded0(int param_1)

{
  short *psVar1;
  uint uVar2;
  
  uVar2 = param_1 + 1;
  psVar1 = &DAT_0057bd40 + uVar2 * 0x43;
  while( true ) {
    if (DAT_005649cc <= uVar2) {
      return 0xffffffff;
    }
    if (*psVar1 == DAT_0058f1f4) {
      return uVar2;
    }
    if (DAT_0058f1f4 == psVar1[1]) {
      return uVar2;
    }
    if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (uint)*(byte *)(psVar1 + 2)) != 0) break;
    if (DAT_00583c20 != 0) {
      return uVar2;
    }
    uVar2 = uVar2 + 1;
    psVar1 = psVar1 + 0x43;
  }
  return uVar2;
}

