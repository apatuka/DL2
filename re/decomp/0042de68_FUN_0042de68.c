// FUN_0042de68 @ 0042de68 size=119 sig=undefined FUN_0042de68() cc=unknown
// callers: 
// callees: FUN_0049ea99,FUN_00491d38,FUN_0049a93f,FUN_0049a8ed,FUN_0049aa64,FUN_0049f22b,FUN_004a43da

undefined4 FUN_0042de68(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    puVar3 = local_14;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,puVar3);
    FUN_0049aa64(local_14);
    iVar2 = FUN_0049ea99(param_1);
    if (*(undefined4 **)(iVar2 + 0x50) != (undefined4 *)0x0) {
      FUN_00491d38(**(undefined4 **)(iVar2 + 0x50));
    }
    FUN_004a43da(param_1,3,param_3,param_4);
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

