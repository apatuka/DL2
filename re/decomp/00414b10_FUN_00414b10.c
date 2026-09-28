// FUN_00414b10 @ 00414b10 size=81 sig=undefined FUN_00414b10() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_0049a8ed,FUN_0049f09b,FUN_0049a93f,FUN_00482320,FUN_0049aa64

undefined4 FUN_00414b10(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    FUN_0049f09b(param_1,local_14);
    FUN_0049aa64(local_14);
    FUN_00482320();
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

