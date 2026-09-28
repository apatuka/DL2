// FUN_00431258 @ 00431258 size=161 sig=undefined FUN_00431258() cc=unknown
// callers: 
// callees: FUN_0049a8ed,FUN_004a43da,FUN_0049ea99,FUN_00412d38,FUN_0049f22b,FUN_0049aa64,FUN_0049a93f

undefined4 FUN_00431258(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
    FUN_004a43da(param_1,3,param_3,param_4);
    if ((((DAT_004c42ec == 0) && (DAT_004c42e4 != 0)) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0'))
       && (DAT_004c42f0 != 0)) {
      iVar2 = FUN_0049ea99(param_1);
      FUN_00412d38(DAT_004c42e4,*(undefined4 *)(iVar2 + 0x3c));
    }
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

