// FUN_00469e50 @ 00469e50 size=51 sig=undefined FUN_00469e50() cc=unknown
// callers: FUN_0046a020
// callees: 

undefined4 FUN_00469e50(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 < 0) {
    uVar1 = 0x40;
  }
  else if (param_1 < 0x280) {
    if (100 < param_2) {
      uVar1 = 0x20;
    }
  }
  else {
    uVar1 = 0x10;
  }
  return uVar1;
}

