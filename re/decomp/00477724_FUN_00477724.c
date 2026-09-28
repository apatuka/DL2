// FUN_00477724 @ 00477724 size=96 sig=undefined FUN_00477724() cc=unknown
// callers: SyncCreateUnit,FUN_00445d30
// callees: FUN_00474d90,FUN_00474cfc,FUN_0047510c,FUN_004779c0,FUN_00445d30

undefined4 FUN_00477724(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_0058f1fc == 0) {
    uVar2 = FUN_00474cfc();
    uVar2 = FUN_00445d30(param_1,param_2,param_3,uVar2);
  }
  else {
    FUN_004779c0(param_2,0x49,param_3,(int)*(short *)(param_1 + 0x1a),0,0,0);
    iVar1 = FUN_00474d90(0x49,param_2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_0047510c(DAT_006535ac);
    }
  }
  return uVar2;
}

