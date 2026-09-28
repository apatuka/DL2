// FUN_00445cd8 @ 00445cd8 size=85 sig=undefined FUN_00445cd8() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00445cd8(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (((*(char *)(param_1 + 0x995) == '\0') || ((&DAT_004faf8d)[param_2 * 0x24] == '\x03')) ||
     (param_2 == 0x1e)) {
    if ((*(char *)(param_1 + 0x996) == '\0') || ((&DAT_004faf8d)[param_2 * 0x24] != '\x03')) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

