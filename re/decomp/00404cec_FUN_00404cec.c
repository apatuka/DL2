// FUN_00404cec @ 00404cec size=106 sig=undefined FUN_00404cec() cc=unknown
// callers: 
// callees: FUN_004504a4,FUN_0045093c

void FUN_00404cec(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = -1;
  if (DAT_0058f1ec == 0) {
    switch(param_3) {
    case 0x1f:
      iVar2 = FUN_00404c74(param_1,param_2,0x4b5684);
      break;
    case 0x20:
      iVar2 = FUN_00404c74(param_1,param_2,0x4b55d0);
      break;
    case 0x21:
      iVar2 = FUN_00404c74(param_1,param_2,0x4b560c);
      break;
    case 0x22:
      iVar2 = FUN_00404c74(param_1,param_2,0x4b5648);
      break;
    case 0x23:
      iVar2 = FUN_00404c74(param_1,param_2,0x4b56c0);
    }
    if (iVar2 - 0x1fU < 5) {
      (**(code **)(&DAT_00404d8d + (iVar2 - 0x1fU) * 4))();
      return;
    }
    if (iVar2 != -1) {
      uVar1 = FUN_004504a4(param_1,iVar2);
      FUN_0045093c(param_1,1 << ((byte)param_2 & 0x1f),iVar2,uVar1,0,0,0);
    }
  }
  return;
}

