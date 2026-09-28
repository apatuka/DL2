// FUN_0048e670 @ 0048e670 size=165 sig=undefined FUN_0048e670() cc=unknown
// callers: FUN_004a2078,FUN_004a08c5
// callees: 

undefined8
FUN_0048e670(undefined4 *param_1,int param_2,uint param_3,int param_4,undefined4 *param_5,
            int param_6)

{
  undefined4 in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 in_EDX;
  undefined4 *puVar3;
  
  uVar1 = param_3 >> 2;
  param_3 = param_3 & 3;
  uVar2 = uVar1;
  puVar3 = param_5;
  if (param_3 == 0) {
    do {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *param_1;
        param_1 = param_1 + 1;
        puVar3 = puVar3 + 1;
      }
      param_1 = (undefined4 *)((int)param_1 + param_4);
      param_5 = (undefined4 *)((int)param_5 + param_6);
      param_2 = param_2 + -1;
      uVar2 = uVar1;
      puVar3 = param_5;
    } while (param_2 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  if (param_3 == 2) {
    do {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *param_1;
        param_1 = param_1 + 1;
        puVar3 = puVar3 + 1;
      }
      *(undefined2 *)puVar3 = *(undefined2 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + param_4 + 2);
      param_5 = (undefined4 *)((int)param_5 + param_6);
      param_2 = param_2 + -1;
      uVar2 = uVar1;
      puVar3 = param_5;
    } while (param_2 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  if (param_3 < 2) {
    do {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *param_1;
        param_1 = param_1 + 1;
        puVar3 = puVar3 + 1;
      }
      *(undefined1 *)puVar3 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + param_4 + 1);
      param_5 = (undefined4 *)((int)param_5 + param_6);
      param_2 = param_2 + -1;
      uVar2 = uVar1;
      puVar3 = param_5;
    } while (param_2 != 0);
    return CONCAT44(in_EDX,in_EAX);
  }
  do {
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = *param_1;
      param_1 = param_1 + 1;
      puVar3 = puVar3 + 1;
    }
    *(undefined2 *)puVar3 = *(undefined2 *)param_1;
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_1 + 2);
    param_1 = (undefined4 *)((int)param_1 + param_4 + 3);
    param_5 = (undefined4 *)((int)param_5 + param_6);
    param_2 = param_2 + -1;
    uVar2 = uVar1;
    puVar3 = param_5;
  } while (param_2 != 0);
  return CONCAT44(in_EDX,in_EAX);
}

