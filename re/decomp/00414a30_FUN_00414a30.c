// FUN_00414a30 @ 00414a30 size=58 sig=undefined FUN_00414a30() cc=unknown
// callers: WinMain
// callees: FUN_00414f38,FUN_00414958,FUN_004493dc

int FUN_00414a30(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = FUN_00414958(param_3,param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if (param_4 != 0) {
      FUN_004493dc(1);
    }
    FUN_00414f38(iVar1);
  }
  return iVar1;
}

