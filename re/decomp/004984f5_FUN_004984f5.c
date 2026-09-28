// FUN_004984f5 @ 004984f5 size=170 sig=undefined FUN_004984f5() cc=unknown
// callers: FUN_00498826
// callees: FUN_004983ae,FUN_004989cf,FUN_00498ba9

int FUN_004984f5(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_10;
  
  iVar3 = FUN_00498ba9(0x2000);
  if (iVar3 == 0) {
    local_10 = -1;
  }
  else {
    iVar1 = *(int *)(param_2 + 8);
    uVar2 = *(undefined4 *)(param_2 + 4);
    local_10 = 0;
    iVar5 = 0;
    if (0 < iVar1) {
      do {
        iVar4 = FUN_004983ae(param_1,param_2,0,iVar5,uVar2,iVar3);
        if (iVar4 < 0) {
          FUN_004989cf(iVar3);
          return -1;
        }
        local_10 = local_10 + iVar4;
        if (param_3 < 0) {
          iVar4 = FUN_004983ae(param_1,param_2,0xffffffff,iVar5,uVar2,iVar3);
          if (iVar4 < 0) {
            FUN_004989cf(iVar3);
            return -1;
          }
          local_10 = local_10 + iVar4;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar1);
    }
    FUN_004989cf(iVar3);
  }
  return local_10;
}

