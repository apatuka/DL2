// FUN_0049d105 @ 0049d105 size=136 sig=undefined FUN_0049d105() cc=unknown
// callers: FUN_0049d315,FUN_0049ee8f
// callees: FUN_00495454,FUN_004955b2,FUN_00498ba9,FUN_00495544,FUN_0048f774,FUN_004954f9

int FUN_0049d105(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_2 + 0x94) == 0) {
    uVar1 = FUN_004955b2(0,0);
    *(undefined4 *)(param_2 + 0x94) = uVar1;
  }
  if ((*(int *)(param_2 + 0x94) == 0) || (iVar2 = FUN_00498ba9(0x2c), iVar2 == 0)) {
    return 0;
  }
  FUN_0048f774(iVar2,0x2c,0);
  if (param_3 < 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3);
  }
  FUN_00495454(*(undefined4 *)(param_2 + 0x94),iVar2,iVar3);
  if (iVar3 != 0) {
    return param_3 + 1;
  }
  iVar2 = FUN_00495544(*(undefined4 *)(param_2 + 0x94));
  return iVar2;
}

