// FUN_0048e89c @ 0048e89c size=133 sig=undefined FUN_0048e89c() cc=unknown
// callers: FUN_00493784,FUN_004935fc,FUN_00493974
// callees: 

undefined8 FUN_0048e89c(int param_1,uint param_2,undefined4 param_3,undefined4 *param_4,int param_5)

{
  undefined4 in_EAX;
  uint uVar1;
  undefined4 in_EDX;
  uint uVar2;
  
  param_5 = param_5 - param_2;
  uVar2 = param_2 >> 2;
  param_2 = param_2 & 3;
  uVar1 = uVar2;
  if (param_2 == 0) {
    do {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *param_4 = param_3;
        param_4 = param_4 + 1;
      }
      param_4 = (undefined4 *)((int)param_4 + param_5);
      param_1 = param_1 + -1;
      uVar1 = uVar2;
    } while (param_1 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  if (param_2 == 2) {
    do {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *param_4 = param_3;
        param_4 = param_4 + 1;
      }
      *(short *)param_4 = (short)param_3;
      param_4 = (undefined4 *)((int)param_4 + param_5 + 2);
      param_1 = param_1 + -1;
      uVar1 = uVar2;
    } while (param_1 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  if (param_2 < 2) {
    do {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *param_4 = param_3;
        param_4 = param_4 + 1;
      }
      *(char *)param_4 = (char)param_3;
      param_4 = (undefined4 *)((int)param_4 + param_5 + 1);
      param_1 = param_1 + -1;
      uVar1 = uVar2;
    } while (param_1 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  do {
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      *param_4 = param_3;
      param_4 = param_4 + 1;
    }
    *(short *)param_4 = (short)param_3;
    *(char *)((int)param_4 + 2) = (char)param_3;
    param_4 = (undefined4 *)((int)param_4 + param_5 + 3);
    param_1 = param_1 + -1;
    uVar1 = uVar2;
  } while (param_1 != 0);
  return CONCAT44(in_EDX,in_EAX);
}

