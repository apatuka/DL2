// FUN_004a87d3 @ 004a87d3 size=75 sig=undefined FUN_004a87d3() cc=unknown
// callers: FUN_004a881e
// callees: FUN_004a881e

void FUN_004a87d3(int param_1,undefined4 param_2,int *param_3,int *param_4,undefined4 param_5,
                 int param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 *puVar1;
  int *piVar2;
  
  while (piVar2 = param_3 + -3, param_4 <= piVar2) {
    puVar1 = (undefined4 *)(param_3[-2] + param_1);
    if (param_6 != 0) {
      puVar1 = (undefined4 *)*puVar1;
    }
    param_3 = piVar2;
    if ((*(byte *)(*piVar2 + 0xc) & 2) != 0) {
      FUN_004a881e(puVar1,*piVar2,param_2,param_5,0,param_7,param_8);
      param_5 = 0;
    }
  }
  return;
}

