// FUN_00437134 @ 00437134 size=173 sig=undefined FUN_00437134() cc=unknown
// callers: FUN_0045d478
// callees: FUN_00436d90,FUN_0045e274,FUN_00436978,FUN_00436a44,FUN_00449d54

undefined4 FUN_00437134(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((char)(&DAT_005a43f0)[(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5] * 0xadc] ==
      DAT_0058f1f4) {
    if (DAT_00558f28 == 0) {
      FUN_0045e274(param_1,param_2);
    }
    else if (DAT_00558f28 == 1) {
      FUN_00449d54((int)(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5]);
    }
    FUN_00436978((int)(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5]);
    FUN_00436a44();
    FUN_00436d90();
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

