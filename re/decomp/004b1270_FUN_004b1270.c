// FUN_004b1270 @ 004b1270 size=81 sig=undefined FUN_004b1270() cc=unknown
// callers: FUN_0041244c
// callees: 

int FUN_004b1270(undefined4 param_1,int param_2,uint param_3,int param_4,code *param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  while( true ) {
    uVar1 = param_3;
    if (uVar1 == 0) {
      return 0;
    }
    param_3 = uVar1 >> 1;
    iVar3 = param_3 * param_4 + param_2;
    iVar2 = (*param_5)(param_1,iVar3);
    if (iVar2 == 0) break;
    if (-1 < iVar2) {
      param_2 = iVar3 + param_4;
      param_3 = (uVar1 - param_3) - 1;
    }
  }
  return iVar3;
}

