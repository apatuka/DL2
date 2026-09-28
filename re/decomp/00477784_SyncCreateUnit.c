// SyncCreateUnit @ 00477784 size=178 sig=undefined SyncCreateUnit() cc=unknown
// callers: FUN_004471c0,ProduceUnits,FUN_0046d2e8,FUN_0047c730,FUN_00438b14
// callees: FUN_00474cfc,FUN_0047510c,FUN_00477724,FUN_004779c0,WaitSync,FUN_00445d30,FUN_00474d0c
// strings: \"SyncCreateUnit\"

/* Network-synchronized unit creation */

undefined2 * SyncCreateUnit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  int iVar3;
  
  if (DAT_0058f1fc == 0) {
    uVar1 = FUN_00474cfc();
    puVar2 = (undefined2 *)FUN_00445d30(param_1,param_2,param_3,uVar1);
  }
  else {
    WaitSync(s_SyncCreateUnit_004dc1ec);
    if (DAT_0058f1f4 == DAT_004d5a58) {
      puVar2 = (undefined2 *)FUN_00477724(param_1,param_2,param_3);
      if (puVar2 == (undefined2 *)0x0) {
        FUN_004779c0(DAT_0058f1f4,0x43,0x49,0,0,0,0);
      }
      else {
        FUN_004779c0(DAT_0058f1f4,0x42,0x49,*puVar2,0,0,0);
      }
    }
    else {
      iVar3 = FUN_00474d0c(0x49);
      if (iVar3 == 2) {
        puVar2 = (undefined2 *)FUN_0047510c(DAT_0065354e);
      }
      else {
        puVar2 = (undefined2 *)0x0;
      }
    }
  }
  return puVar2;
}

