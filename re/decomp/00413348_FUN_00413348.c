// FUN_00413348 @ 00413348 size=129 sig=undefined FUN_00413348() cc=unknown
// callers: Timer_Init,FUN_00412d38,FUN_00413250
// callees: FUN_0048c85e,FUN_0048d54f,FUN_0048d5c4

void FUN_00413348(int *param_1,undefined4 param_2,int param_3,int param_4)

{
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*param_1 != 0) {
    FUN_0048d54f(*(undefined4 *)((int)param_1 + 0xe),param_2);
    FUN_0048d5c4(param_2);
    local_14 = 0;
    local_10 = 0;
    local_c = 199;
    local_8 = 199;
    local_24 = param_3;
    local_1c = param_3 + 199;
    local_20 = param_4;
    local_18 = param_4 + 199;
    FUN_0048c85e(*(undefined4 *)((int)param_1 + 0xe),param_2,&local_14,&local_24,&local_14,&local_24
                 ,0);
  }
  return;
}

