// FUN_004943ab @ 004943ab size=158 sig=undefined FUN_004943ab() cc=unknown
// callers: FUN_00444398,FUN_0049497a
// callees: FUN_00494346,FUN_0048c85e

undefined4 FUN_004943ab(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_0051dc8c = 0;
  if (param_2 == (int *)0x0) {
    param_2 = &DAT_0065ec8c;
  }
  if (param_1 == 0) {
    param_1 = DAT_0065ecac;
  }
  iVar1 = FUN_00494346(param_2[2] - *param_2,param_2[3] - param_2[1]);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    local_14 = 0;
    local_10 = 0;
    local_c = *(undefined4 *)(DAT_0065ecb8 + 4);
    local_8 = *(undefined4 *)(DAT_0065ecb8 + 8);
    FUN_0048c85e(param_1,DAT_0065ecb8,param_2,&local_14,0,0,0);
    DAT_0051dc8c = 1;
    piVar3 = &DAT_0065ec9c;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *param_2;
      param_2 = param_2 + 1;
      piVar3 = piVar3 + 1;
    }
    uVar2 = 1;
  }
  return uVar2;
}

