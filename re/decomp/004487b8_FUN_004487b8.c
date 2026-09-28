// FUN_004487b8 @ 004487b8 size=140 sig=undefined FUN_004487b8() cc=unknown
// callers: FUN_00448844,FUN_00448d1c
// callees: FUN_004023dc,FUN_00448700,FUN_00475ce8,FUN_004485e8,FUN_004483d0

undefined4 FUN_004487b8(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = FUN_004485e8(param_1,param_2,param_3);
  iVar2 = FUN_00448700(param_1,iVar1,param_3);
  if ((iVar1 != 0) && (iVar2 != 0)) {
    if (0x16 < param_2) {
      param_2 = 0xb;
    }
    uVar3 = FUN_004023dc(iVar1,param_2);
    if (0x16 < param_3) {
      param_3 = 0xb;
    }
    uVar4 = FUN_004023dc(iVar2,param_3);
    local_8 = FUN_00475ce8(param_1,iVar1,uVar3,iVar2,uVar4);
  }
  FUN_004483d0(param_1);
  return local_8;
}

