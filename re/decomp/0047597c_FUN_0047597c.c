// FUN_0047597c @ 0047597c size=109 sig=undefined FUN_0047597c() cc=unknown
// callers: FUN_0044dcc8,FUN_00408310,FUN_00402d58
// callees: FUN_0044db50,FUN_004750c4,FUN_004779c0,FUN_00474d90,FUN_00474cfc

undefined4 FUN_0047597c(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_0058f1fc == 0) {
    uVar2 = FUN_00474cfc();
    uVar2 = FUN_0044db50(param_1,param_2,param_3,uVar2);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x15,param_2 << 8 | (int)*(short *)(param_1 + 0x1a),
                 0,param_3,0,0);
    iVar1 = FUN_00474d90(0x15,(int)*(char *)(param_1 + 0x20));
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_004750c4(DAT_006535aa);
    }
  }
  return uVar2;
}

