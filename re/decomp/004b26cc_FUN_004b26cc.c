// FUN_004b26cc @ 004b26cc size=179 sig=undefined FUN_004b26cc() cc=unknown
// callers: 
// callees: SetConsoleCtrlHandler,FUN_004b366c,FUN_004b2500,FUN_004b0b44,FUN_004b12c4

undefined4 FUN_004b26cc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  if (DAT_00521434 == '\0') {
    DAT_0069f3a0 = FUN_004b2520;
    SetConsoleCtrlHandler(FUN_004b26a8,1);
    DAT_00521434 = '\x01';
  }
  iVar1 = FUN_004b2500(param_1);
  if (iVar1 == -1) {
    puVar2 = (undefined4 *)FUN_004b12c4();
    *puVar2 = 0x13;
    uVar3 = 0xffffffff;
  }
  else {
    if ((param_1 == 2) || (param_1 == 0x15)) {
      puVar2 = (undefined4 *)&DAT_00521438;
    }
    else {
      iVar4 = FUN_004b366c();
      if (iVar4 == 0) {
        return 0xffffffff;
      }
      puVar2 = *(undefined4 **)(iVar4 + 0x28);
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)FUN_004b0b44(0x28);
        if (puVar2 == (undefined4 *)0x0) {
          puVar2 = (undefined4 *)FUN_004b12c4();
          *puVar2 = 8;
          return 0xffffffff;
        }
        iVar6 = 0;
        puVar5 = puVar2;
        do {
          iVar6 = iVar6 + 1;
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        } while (iVar6 < 10);
        *(undefined4 **)(iVar4 + 0x28) = puVar2;
      }
    }
    uVar3 = puVar2[iVar1];
    puVar2[iVar1] = param_2;
  }
  return uVar3;
}

