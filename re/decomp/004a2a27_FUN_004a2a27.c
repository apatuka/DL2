// FUN_004a2a27 @ 004a2a27 size=159 sig=undefined FUN_004a2a27() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049ea99,FUN_0049c0e4,FUN_0049f09b

undefined4 FUN_004a2a27(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (*(int *)(param_1 + 0x1c) == 9) {
    if (param_4 == 3) {
      param_3 = param_3 - param_6;
      param_2 = param_2 - param_5;
      uVar1 = FUN_0049ea99(param_1);
      uVar1 = FUN_0049c0e4(uVar1,param_1,param_2,param_3);
      return uVar1;
    }
    if (((*(byte *)(param_1 + 0x27) & 0x20) != 0) && ((param_4 == 5 || (param_4 == 6)))) {
      uVar1 = FUN_0049ea99(param_1);
      uVar1 = FUN_0049c0e4(uVar1,param_1,param_2,param_3);
      return uVar1;
    }
  }
  if (((((*(byte *)(param_1 + 0x28) & 4) == 0) && ((*(byte *)(param_1 + 0x28) & 0x80) == 0)) &&
      (0 < *(int *)(param_1 + 0x104))) &&
     (((FUN_0049f09b(param_1,&local_14), local_14 <= param_2 && (param_2 < local_c)) &&
      ((local_10 <= param_3 && (param_3 < local_8)))))) {
    return 1;
  }
  return 0;
}

