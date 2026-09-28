// FUN_004b35b4 @ 004b35b4 size=33 sig=undefined FUN_004b35b4() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004b35b4(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_005217f0;
  DAT_005217f0 = param_1;
  if (param_1 == 0) {
    DAT_005217f0 = 1;
  }
  return uVar1;
}

