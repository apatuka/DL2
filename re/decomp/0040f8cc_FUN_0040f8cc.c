// FUN_0040f8cc @ 0040f8cc size=166 sig=undefined FUN_0040f8cc() cc=unknown
// callers: FUN_0041026c
// callees: FUN_0040f874,FUN_0040f5e0,FUN_0044b5bc,FUN_00484e88,FUN_0040f700

undefined4 FUN_0040f8cc(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_10;
  undefined *local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = (undefined *)0x0;
  local_10 = 10000;
  if (param_2 != -1) {
    local_c = &DAT_005a43d0 + param_2 * 0xadc;
  }
  puVar5 = &DAT_00521bb4;
  do {
    uVar1 = *puVar5;
    iVar2 = FUN_0040f874(uVar1,param_1);
    if (iVar2 != 0) {
      iVar2 = FUN_0040f700(uVar1,local_c,param_1,param_3);
      if (iVar2 != 0) {
        uVar3 = FUN_0040f5e0(param_1);
        iVar2 = FUN_0044b5bc(uVar1,uVar3);
        if (iVar2 != 0) {
          iVar4 = FUN_00484e88(iVar2);
          if (iVar4 < local_10) {
            local_10 = FUN_00484e88(iVar2);
            local_8 = uVar1;
          }
        }
      }
    }
    puVar5 = (undefined4 *)puVar5[1];
  } while (puVar5 != &DAT_00521bb4);
  return local_8;
}

