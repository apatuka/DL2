// FUN_0049d1dd @ 0049d1dd size=162 sig=undefined FUN_0049d1dd() cc=unknown
// callers: FUN_0049d315,FUN_0049ee8f,FUN_0049ef47
// callees: strlen,FUN_00498ba9,FUN_004954f9,FUN_004989cf,FUN_004a6964,FUN_0048f7f1

undefined4 FUN_0049d1dd(undefined4 param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((*(int *)(param_2 + 0x94) == 0) ||
     (iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3), iVar1 == 0)) {
    uVar3 = 0;
  }
  else {
    if (param_4 == 0) {
      if (*(int *)(iVar1 + 0x10) != 0) {
        FUN_004989cf(*(undefined4 *)(iVar1 + 0x10));
        *(undefined4 *)(iVar1 + 0x10) = 0;
      }
      if ((param_5 != 0) && (iVar2 = strlen(param_5), iVar2 != 0)) {
        iVar2 = strlen(param_5);
        iVar2 = FUN_00498ba9(iVar2 + 1);
        *(int *)(iVar1 + 0x10) = iVar2;
        if (iVar2 != 0) {
          FUN_004a6964(*(undefined4 *)(iVar1 + 0x10),param_5);
        }
      }
    }
    else if (param_4 == 1) {
      FUN_0048f7f1(param_5,iVar1 + 0x14,0x18);
    }
    else if (param_4 == 2) {
      *(int *)(iVar1 + 8) = param_5;
    }
    uVar3 = 1;
  }
  return uVar3;
}

