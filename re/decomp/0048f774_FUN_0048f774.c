// FUN_0048f774 @ 0048f774 size=92 sig=undefined FUN_0048f774() cc=unknown
// callers: FUN_00492578,FUN_0049ddf8,FUN_00490fb0,FUN_00489ae1,FUN_004a18c5,FUN_0049164f,FUN_0048f8e8,FUN_00496358,FUN_00495b72,FUN_00495596,FUN_0049659f,FUN_00489084,FUN_004983ae,FUN_00489ef5,FUN_0049d105,FUN_0048a145,FUN_004a4c92,FUN_004a3b3c,FUN_0048bc0d,FUN_0049d315,FUN_004a57e0,FUN_0048d740,FUN_00493108,FUN_004897ea,FUN_0048bf93,FUN_0048be9b,FUN_004a4273,FUN_0049585a,FUN_004639f4,FUN_004a3439
// callees: 

undefined8 FUN_0048f774(undefined4 *param_1,uint param_2,undefined1 param_3)

{
  undefined2 uVar1;
  undefined4 in_EAX;
  uint uVar2;
  undefined4 in_EDX;
  undefined4 uStack_18;
  
  if (param_2 != 0) {
    uVar1 = CONCAT11(param_3,param_3);
    uStack_18 = CONCAT22(uVar1,uVar1);
    uVar2 = param_2 >> 2;
    param_2 = param_2 & 3;
    if (param_2 != 0) {
      if (param_2 == 2) {
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          *param_1 = uStack_18;
          param_1 = param_1 + 1;
        }
        *(undefined2 *)param_1 = uVar1;
        return CONCAT44(in_EDX,in_EAX);
      }
      if (param_2 < 2) {
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          *param_1 = uStack_18;
          param_1 = param_1 + 1;
        }
        *(undefined1 *)param_1 = param_3;
        return CONCAT44(in_EDX,in_EAX);
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *param_1 = uStack_18;
        param_1 = param_1 + 1;
      }
      *(undefined2 *)param_1 = uVar1;
      *(undefined1 *)((int)param_1 + 2) = param_3;
      return CONCAT44(in_EDX,in_EAX);
    }
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_1 = uStack_18;
      param_1 = param_1 + 1;
    }
  }
  return CONCAT44(in_EDX,in_EAX);
}

