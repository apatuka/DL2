// FUN_0049a72d @ 0049a72d size=51 sig=undefined FUN_0049a72d() cc=unknown
// callers: FUN_0049ae0c,FUN_0048c662,FUN_0049a760
// callees: 

undefined4 FUN_0049a72d(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0x80008) {
    uVar1 = 0;
  }
  else if (param_1 == 0x100008) {
    uVar1 = 1;
  }
  else if (param_1 == 0x100010) {
    uVar1 = 2;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

