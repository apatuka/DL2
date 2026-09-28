// FUN_0043ae78 @ 0043ae78 size=85 sig=undefined FUN_0043ae78() cc=unknown
// callers: 
// callees: FUN_0049a8ed,FUN_0049f09b,FUN_0049aa64,FUN_0049a93f,FUN_004a43da,FUN_00482320

undefined4 FUN_0043ae78(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    FUN_0049f09b(param_1,local_14);
    iVar1 = FUN_0049aa64(local_14);
    if (iVar1 != 0) {
      FUN_00482320();
    }
    FUN_0049a93f();
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

