// FUN_0040f818 @ 0040f818 size=92 sig=undefined FUN_0040f818() cc=unknown
// callers: FUN_0041026c
// callees: FUN_0040f6b0,FUN_0040f700

undefined4 FUN_0040f818(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  
  puVar4 = (undefined *)0x0;
  if (param_2 != -1) {
    puVar4 = &DAT_005a43d0 + param_2 * 0xadc;
  }
  puVar3 = &DAT_00521bb4;
  while( true ) {
    uVar1 = *puVar3;
    iVar2 = FUN_0040f6b0(uVar1,param_1);
    if ((iVar2 != 0) && (iVar2 = FUN_0040f700(uVar1,puVar4,param_1,param_3), iVar2 != 0)) break;
    puVar3 = (undefined4 *)puVar3[1];
    if (puVar3 == &DAT_00521bb4) {
      return 0;
    }
  }
  return uVar1;
}

