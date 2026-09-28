// FUN_00493974 @ 00493974 size=250 sig=undefined FUN_00493974() cc=unknown
// callers: FUN_00493a6e
// callees: FUN_00499b9f,FUN_0048e89c,FUN_0048d03e

void FUN_00493974(int param_1,int param_2,int param_3,int param_4,uint param_5,int param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 < *(int *)(param_6 + 0x34)) {
    if (param_1 < *(int *)(param_6 + 0x2c)) {
      param_1 = *(int *)(param_6 + 0x2c);
    }
    if (*(int *)(param_6 + 0x2c) <= param_3) {
      if (*(int *)(param_6 + 0x34) < param_3) {
        param_3 = *(int *)(param_6 + 0x34);
      }
      if ((param_1 < param_3) && (param_2 < *(int *)(param_6 + 0x38))) {
        if (param_2 < *(int *)(param_6 + 0x30)) {
          param_2 = *(int *)(param_6 + 0x30);
        }
        if (param_4 != *(int *)(param_6 + 0x30)) {
          if (*(int *)(param_6 + 0x38) < param_4) {
            param_4 = *(int *)(param_6 + 0x38);
          }
          if (param_2 < param_4) {
            if ((param_5 & 0x80000000) != 0) {
              param_5 = FUN_00499b9f(param_6,param_5);
            }
            if (*(int *)(param_6 + 0xc) == 8) {
              param_5 = param_5 & 0xff;
              param_5 = param_5 | param_5 << 8 | param_5 << 0x10 | param_5 << 0x18;
            }
            else if (*(int *)(param_6 + 0xc) == 0x10) {
              param_5 = param_5 & 0xffff | (param_5 & 0xffff) << 0x10;
            }
            uVar2 = *(undefined4 *)(param_6 + 0x10);
            uVar1 = FUN_0048d03e(param_6,param_1,param_2);
            FUN_0048e89c(param_4 - param_2,(param_3 - param_1) * (*(int *)(param_6 + 0xc) + 7 >> 3),
                         param_5,uVar1,uVar2);
          }
        }
      }
    }
  }
  return;
}

