// FUN_00482de8 @ 00482de8 size=156 sig=undefined FUN_00482de8() cc=unknown
// callers: FUN_0043da00
// callees: FUN_00482ba0,FUN_0048a0fc

void FUN_00482de8(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (param_2 != 0) {
    if (param_2 == DAT_004dcedc) {
      FUN_0048a0fc(DAT_004dcee0,param_3);
    }
    else if (param_2 == DAT_004dcee4) {
      FUN_0048a0fc(DAT_004dcee8,param_3);
    }
    else if ((DAT_004dcedc == 0) || (DAT_004dcee4 == 0)) {
      iVar1 = FUN_00482ba0(param_1,1,1,0,param_3,0,0);
      if (iVar1 != 0) {
        if (DAT_004dcedc == 0) {
          DAT_004dcedc = param_2;
          DAT_004dcee0 = iVar1;
        }
        else if (DAT_004dcee4 == 0) {
          DAT_004dcee4 = param_2;
          DAT_004dcee8 = iVar1;
        }
      }
    }
  }
  return;
}

