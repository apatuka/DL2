// FUN_00493ae2 @ 00493ae2 size=66 sig=undefined FUN_00493ae2() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00493ae2(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    uVar1 = 0;
  }
  else {
    DAT_0065ec78 = DAT_0065ec78 * 0x6d25 + 1;
    uVar1 = (undefined4)
            ((longlong)(ulonglong)(DAT_0065ec78 & 0x3fffffff) /
            (longlong)((param_1 + 0x3fffffff) / param_1));
  }
  return uVar1;
}

