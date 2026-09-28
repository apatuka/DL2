// FUN_00477888 @ 00477888 size=121 sig=undefined FUN_00477888() cc=unknown
// callers: SyncCreateBuilding
// callees: FUN_00474d90,FUN_00474cfc,FUN_0044dcf4,FUN_004779c0,FUN_004750c4

undefined4 FUN_00477888(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (DAT_0058f1fc == 0) {
    if (param_2 == 0x26) {
      uVar2 = FUN_00474cfc(param_3);
    }
    else {
      uVar2 = 0;
    }
    uVar3 = FUN_00474cfc(uVar2);
    uVar2 = FUN_0044dcf4(param_1,param_2,uVar3,uVar2,param_3);
  }
  else {
    FUN_004779c0(DAT_0058f1f4,0x4a,param_2,(int)*(short *)(param_1 + 0x1a),0,(int)(short)param_3,0);
    iVar1 = FUN_00474d90(0x4a,(int)(short)param_3);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_004750c4(DAT_006535ac);
    }
  }
  return uVar2;
}

