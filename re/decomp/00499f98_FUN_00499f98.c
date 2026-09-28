// FUN_00499f98 @ 00499f98 size=63 sig=undefined FUN_00499f98() cc=unknown
// callers: FUN_004a52db
// callees: 

undefined4 FUN_00499f98(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 1) {
    uVar1 = 8;
  }
  else if (param_1 == 2) {
    uVar1 = 0x10;
  }
  else if (param_1 == 3) {
    uVar1 = 0x18;
  }
  else {
    uVar1 = DAT_0065e590;
    if (param_1 == 4) {
      uVar1 = 0x20;
    }
  }
  return uVar1;
}

