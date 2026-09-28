// FUN_004056fc @ 004056fc size=99 sig=undefined FUN_004056fc() cc=unknown
// callers: FUN_004107ec,FUN_0040d1a4,FUN_0040cdfc,FUN_00408b58,FUN_00408288,FUN_00410558,FUN_00407d60,FUN_004100e0,FUN_0040cffc,FUN_004101d4,FUN_00408f58,FUN_0040d338
// callees: 

undefined4 FUN_004056fc(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    *(undefined4 *)(param_2 + 0x14) = (&DAT_00522294)[param_1 * 0x11];
    *(undefined4 **)(param_2 + 0x18) = &DAT_00522280 + param_1 * 0x11;
    if ((&DAT_00522294)[param_1 * 0x11] != 0) {
      *(int *)((&DAT_00522294)[param_1 * 0x11] + 0x18) = param_2;
    }
    (&DAT_00522294)[param_1 * 0x11] = param_2;
    uVar1 = 1;
  }
  return uVar1;
}

