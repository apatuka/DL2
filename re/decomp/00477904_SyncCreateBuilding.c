// SyncCreateBuilding @ 00477904 size=187 sig=undefined SyncCreateBuilding() cc=unknown
// callers: FUN_00485668,FUN_00466508,FUN_0046d2e8,FUN_0047c730,FUN_0045eadc
// callees: FUN_00474cfc,FUN_0044dcf4,FUN_00477888,FUN_004779c0,WaitSync,FUN_004750c4,FUN_00474d0c
// strings: \"SyncCreateBuilding\"

/* Network-synchronized building creation */

undefined2 * SyncCreateBuilding(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (DAT_0058f1fc == 0) {
    uVar5 = 0xffffffff;
    if (param_2 == 0x26) {
      uVar1 = FUN_00474cfc(0xffffffff);
    }
    else {
      uVar1 = 0;
    }
    uVar2 = FUN_00474cfc(uVar1);
    puVar3 = (undefined2 *)FUN_0044dcf4(param_1,param_2,uVar2,uVar1,uVar5);
  }
  else {
    WaitSync(s_SyncCreateBuilding_004dc1fb);
    if (DAT_0058f1f4 == DAT_004d5a58) {
      puVar3 = (undefined2 *)FUN_00477888(param_1,param_2,0xffffffff);
      if (puVar3 == (undefined2 *)0x0) {
        FUN_004779c0(DAT_0058f1f4,0x43,0x4a,0,0,0,0);
      }
      else {
        FUN_004779c0(DAT_0058f1f4,0x42,0x4a,*puVar3,0,0,0);
      }
    }
    else {
      iVar4 = FUN_00474d0c(0x4a);
      if (iVar4 == 2) {
        puVar3 = (undefined2 *)FUN_004750c4(DAT_0065354e);
      }
      else {
        puVar3 = (undefined2 *)0x0;
      }
    }
  }
  return puVar3;
}

