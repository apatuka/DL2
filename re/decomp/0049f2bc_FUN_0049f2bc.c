// FUN_0049f2bc @ 0049f2bc size=98 sig=undefined FUN_0049f2bc() cc=unknown
// callers: FUN_004a24f1
// callees: FUN_0049f09b

undefined4 * FUN_0049f2bc(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (*(int *)(param_1 + 300) != 0) {
    if (param_4 == (undefined4 *)0x0) {
      param_4 = *(undefined4 **)(*(int *)(param_1 + 300) + 4);
    }
    for (; param_4 != (undefined4 *)0x0; param_4 = (undefined4 *)*param_4) {
      FUN_0049f09b(param_4,&local_14);
      if ((((local_14 <= param_2) && (param_2 < local_c)) && (local_10 <= param_3)) &&
         (param_3 < local_8)) {
        return param_4;
      }
    }
  }
  return (undefined4 *)0x0;
}

