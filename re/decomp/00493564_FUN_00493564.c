// FUN_00493564 @ 00493564 size=110 sig=undefined FUN_00493564() cc=unknown
// callers: 
// callees: FUN_0048e0b7,CYGame_CreateWindow,FUN_0049a760,FUN_0048de1d,FUN_0048dd95,FUN_00498d22,FUN_0048baa6

undefined4
FUN_00493564(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = CYGame_CreateWindow(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_0048baa6(param_5,param_6);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      iVar1 = FUN_00498d22(param_5,0x1000);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        iVar1 = FUN_0049a760(param_3);
        if (iVar1 == 0) {
          uVar2 = 0;
        }
        else {
          FUN_0048dd95();
          FUN_0048de1d();
          FUN_0048e0b7();
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}

