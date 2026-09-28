// FUN_00482ba0 @ 00482ba0 size=234 sig=undefined FUN_00482ba0() cc=unknown
// callers: FUN_00482b38,FUN_00482ac4,FUN_00482d3c,FUN_00482de8
// callees: FUN_004961e8,FUN_00496199,FUN_0048a766,FUN_00495fc5,FUN_0048a489,FUN_004960fd,FUN_0048a333,FUN_0048a06a,FUN_0046ca40,FUN_0048a440,FUN_0048a0fc

int FUN_00482ba0(undefined4 param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                undefined4 param_6,int param_7)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int local_8;
  
  FUN_004960fd();
  if (param_4 == 0) {
    iVar1 = FUN_00496199(0,param_1);
  }
  else {
    iVar1 = FUN_004961e8(0,param_1);
  }
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    FUN_0048a0fc(iVar1,param_5);
    if (param_4 == 0) {
      FUN_0048a06a(iVar1,DAT_00657e24);
    }
    else {
      FUN_0048a06a(iVar1,DAT_00657e28);
    }
    if (param_3 != 0) {
      FUN_0048a489(iVar1,&local_8);
      uVar2 = FUN_0046ca40();
      local_8 = local_8 + (int)(local_8 * (0xf - uVar2 % 0x1f)) / 100;
      FUN_0048a440(iVar1,local_8);
    }
    iVar3 = param_2;
    if (param_4 != 0) {
      iVar3 = 1;
    }
    if (param_2 == 2) {
      FUN_0048a766(iVar1,FUN_00482f28);
    }
    if (param_7 == 0) {
      iVar3 = FUN_0048a333(iVar1,iVar3);
      if (iVar3 == 0) {
        FUN_00495fc5(iVar1);
        iVar1 = 0;
      }
      else {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 2;
      }
    }
  }
  return iVar1;
}

