// FUN_0049f7c9 @ 0049f7c9 size=47 sig=undefined FUN_0049f7c9() cc=unknown
// callers: FUN_0049c244,FUN_0049b7f0,FUN_0049cf41,FUN_0049e3d7,FUN_004a43da,FUN_0049c14c
// callees: FUN_0049ea99,FUN_0049eb20,FUN_0049efae

void FUN_0049f7c9(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_14 [16];
  
  if (param_1 != 0) {
    FUN_0049efae(param_1,local_14);
    puVar2 = local_14;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049eb20(uVar1,puVar2);
  }
  return;
}

