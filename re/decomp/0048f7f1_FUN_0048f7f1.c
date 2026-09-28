// FUN_0048f7f1 @ 0048f7f1 size=73 sig=undefined FUN_0048f7f1() cc=unknown
// callers: FUN_0049d27f,FUN_00498c06,FUN_0048c662,FUN_00490fb0,FUN_00497d40,FUN_00490e6e,FUN_00492cf5,FUN_0048d7da,FUN_0049d1dd,FUN_0048b165,FUN_00498bba,FUN_00496358,FUN_004a5fcf,FUN_0049ae0c,FUN_004a60b1,FUN_004903d6,FUN_004a54e5,FUN_004a1535,FUN_004a65e0,FUN_0048c4eb,FUN_00498c3e,FUN_004a5f16,FUN_0048d205,FUN_00490ce4,FUN_00490bca,FUN_0049aa95,FUN_004a5edf,FUN_0048a667,FUN_00491d38,FUN_0048f992,FUN_0049e007
// callees: 

undefined4 FUN_0048f7f1(undefined2 *param_1,undefined2 *param_2,uint param_3)

{
  undefined4 in_EAX;
  uint uVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  if (param_3 != 0) {
    if (param_1 < param_2) {
      uVar1 = param_3 >> 1;
      puVar2 = (undefined2 *)((int)param_1 + (param_3 - 2));
      puVar3 = (undefined2 *)((int)param_2 + (param_3 - 2));
      if ((param_3 & 1) != 0) {
        *(undefined1 *)((int)param_2 + (param_3 - 1)) =
             *(undefined1 *)((int)param_1 + (param_3 - 1));
        if (uVar1 == 0) {
          return in_EAX;
        }
        puVar2 = (undefined2 *)((int)param_1 + (param_3 - 3));
        puVar3 = (undefined2 *)((int)param_2 + (param_3 - 3));
      }
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + -1;
        puVar3 = puVar3 + -1;
      }
    }
    else {
      uVar1 = param_3 >> 1;
      if ((param_3 & 1) != 0) {
        *(undefined1 *)param_2 = *(undefined1 *)param_1;
        param_1 = (undefined2 *)((int)param_1 + 1);
        param_2 = (undefined2 *)((int)param_2 + 1);
        if (uVar1 == 0) {
          return in_EAX;
        }
      }
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *param_2 = *param_1;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
      }
    }
  }
  return in_EAX;
}

