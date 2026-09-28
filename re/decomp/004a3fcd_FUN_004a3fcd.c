// FUN_004a3fcd @ 004a3fcd size=48 sig=undefined FUN_004a3fcd() cc=unknown
// callers: DisableMainInterface,FUN_0043acd4,DisableMainInterface_c1a4
// callees: FUN_0049f83e

void FUN_004a3fcd(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_1 != 0) {
    uVar1 = 0x80;
    if (param_2 == 0) {
      uVar1 = 0;
    }
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xffffff7f | uVar1;
    FUN_0049f83e(param_1);
  }
  return;
}

