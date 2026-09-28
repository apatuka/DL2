// FUN_0048477c @ 0048477c size=75 sig=undefined FUN_0048477c() cc=unknown
// callers: FUN_0045a6e4,FUN_00480150,DrawSTileBuilding,FUN_00484818,FUN_0045a8a4
// callees: FUN_004845b8,FUN_0048459c,FUN_0048468c

void FUN_0048477c(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  
  if (param_3 != 0) {
    iVar1 = FUN_0048459c(param_3,param_5);
    param_1 = param_1 + iVar1;
  }
  if (param_4 != 0) {
    iVar1 = FUN_004845b8(param_4,param_5);
    param_2 = param_2 + iVar1;
  }
  FUN_0048468c(param_1,param_2,param_5,param_6,param_7);
  return;
}

