// FUN_0049d27f @ 0049d27f size=150 sig=undefined FUN_0049d27f() cc=unknown
// callers: FUN_0049ef88
// callees: strlen,FUN_004954f9,FUN_004a6964,FUN_0048f7f1

undefined4
FUN_0049d27f(undefined4 param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(int *)(param_2 + 0x94) == 0) ||
     (iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    if (param_4 == 0) {
      if (param_5 == (undefined4 *)0x0) {
        if (*(int *)(iVar1 + 0x10) != 0) {
          uVar2 = strlen(*(undefined4 *)(iVar1 + 0x10));
          return uVar2;
        }
        return 0;
      }
      if (*(int *)(iVar1 + 0x10) == 0) {
        *param_5 = 0;
      }
      else {
        FUN_004a6964(param_5,*(undefined4 *)(iVar1 + 0x10));
      }
    }
    else if (param_4 == 1) {
      if (param_5 != (undefined4 *)0x0) {
        FUN_0048f7f1(iVar1 + 0x14,param_5,0x18);
      }
    }
    else if ((param_4 == 2) && (param_5 != (undefined4 *)0x0)) {
      *param_5 = *(undefined4 *)(iVar1 + 8);
    }
    uVar2 = 1;
  }
  return uVar2;
}

