// FUN_0041f2c8 @ 0041f2c8 size=139 sig=undefined FUN_0041f2c8() cc=unknown
// callers: 
// callees: FUN_0049ea99,FUN_0049aa64,FUN_0049a93f,FUN_0049a8ed,FUN_0049f22b,FUN_004a43da,FUN_00412d38

undefined4 FUN_0041f2c8(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    puVar2 = local_14;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,puVar2);
    FUN_0049aa64(local_14);
    FUN_004a43da(param_1,3,param_3,param_4);
    if (((DAT_004b7990 == 0) && (DAT_004b7988 != 0)) && (*(char *)(DAT_004b7988 + 0x3c) == '\0')) {
      FUN_00412d38(DAT_004b7988,*(undefined4 *)(DAT_004b7974 + 0x3c));
    }
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

