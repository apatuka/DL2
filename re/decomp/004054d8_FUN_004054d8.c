// FUN_004054d8 @ 004054d8 size=81 sig=undefined FUN_004054d8() cc=unknown
// callers: FUN_00408bf4,FUN_0040cea4,FUN_00408e3c,FUN_0040d3bc,FUN_00407dfc
// callees: FUN_0040548c

undefined4 FUN_004054d8(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if (param_2 == 0) {
    puVar3 = &DAT_00521bb4;
    do {
      iVar1 = FUN_0040548c(*puVar3,param_1);
      if (iVar1 != 0) {
        return 0;
      }
      puVar3 = (undefined4 *)puVar3[1];
    } while (puVar3 != &DAT_00521bb4);
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_0040548c(param_2,param_1);
    if (iVar1 == 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

