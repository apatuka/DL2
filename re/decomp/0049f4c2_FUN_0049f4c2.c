// FUN_0049f4c2 @ 0049f4c2 size=319 sig=undefined FUN_0049f4c2() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049eb44,FUN_0049f267,FUN_0049f28c,FUN_0049f09b,FUN_0049f31e,FUN_0049ee70

undefined4 *
FUN_0049f4c2(int param_1,int param_2,int param_3,undefined4 *param_4,int *param_5,int *param_6)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_5 != (int *)0x0) {
    *param_5 = 0;
  }
  if (param_6 != (int *)0x0) {
    *param_6 = 0;
  }
  if (*(int *)(param_1 + 300) != 0) {
    for (puVar1 = *(undefined4 **)(*(int *)(param_1 + 300) + 4); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((((DAT_0051dca4 & 2) != 0) ||
          (((*(byte *)(puVar1 + 10) & 4) == 0 && ((*(byte *)(puVar1 + 10) & 0x80) == 0)))) &&
         ((0 < (int)puVar1[0x41] &&
          ((((FUN_0049f09b(puVar1,&local_18), local_18 <= param_2 && (param_2 < local_10)) &&
            (local_14 <= param_3)) && (param_3 < local_c)))))) {
        iVar2 = FUN_0049ee70(puVar1);
        if (iVar2 == 0) {
          uVar3 = FUN_0049f267(param_1,puVar1,param_2,param_3);
          *param_4 = uVar3;
          FUN_0049f28c(param_1,puVar1,*param_4,&local_18);
          if (param_5 != (int *)0x0) {
            *param_5 = param_2 - local_18;
          }
          if (param_6 == (int *)0x0) {
            return puVar1;
          }
          *param_6 = param_3 - local_14;
          return puVar1;
        }
        local_8 = FUN_0049f31e(param_1,puVar1,param_2,param_3,param_5,param_6);
        if ((local_8 != -1) && (iVar2 = FUN_0049eb44(param_1,puVar1,2,0x1f,local_8,0), iVar2 != 2))
        {
          *param_4 = 0;
          return puVar1;
        }
      }
    }
  }
  return (undefined4 *)0x0;
}

