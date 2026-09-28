// FUN_004073e4 @ 004073e4 size=432 sig=undefined FUN_004073e4() cc=unknown
// callers: FUN_0040350c
// callees: FUN_004412d4,FUN_00406a58,FUN_00476aac,FUN_0040526c,FUN_00406b1c,FUN_00406d10,FUN_00477f9c,FUN_00476c44,FUN_004767f0,FUN_00441388,FUN_0045093c

undefined4 FUN_004073e4(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = 0;
  if (DAT_004d5af4 == 0) {
    return 0;
  }
  if (DAT_0059f154 - (&DAT_0052245c)[param_1 * 7 + param_2] < 5) {
    return 0;
  }
  local_c = -1;
  local_10 = -1;
  local_14 = &DAT_0059f161;
  iVar3 = 0;
  do {
    if (*local_14 != '\0') {
      iVar1 = FUN_004412d4(param_1,iVar3,0x10);
      if (iVar1 != 0) {
        local_c = iVar3;
      }
      iVar1 = FUN_00441388(param_2,iVar3,0x10);
      if (iVar1 != 0) {
        local_10 = iVar3;
      }
    }
    iVar3 = iVar3 + 1;
    local_14 = local_14 + 0x2d8;
  } while (iVar3 < 7);
  FUN_0040526c(param_1,param_2,0x14);
  if (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < 0) {
    return 0;
  }
  iVar3 = FUN_00406b1c(param_1,param_2,0x10,0);
  if (iVar3 == 0) {
    return 0;
  }
  if (local_10 != -1) {
    FUN_0045093c(param_1,1 << ((byte)param_2 & 0x1f),0xffffffff,9,local_10,0,0);
    return 0;
  }
  if (local_c != -1) {
    FUN_0040526c(param_1,local_c,0xffffffec);
    iVar3 = FUN_00406a58(param_1,local_c,0x10);
    if (iVar3 == 0) {
      return 0;
    }
    FUN_00476aac(param_1,local_c,0x10);
  }
  uVar2 = FUN_00406d10(param_1,param_2,0x10);
  (&DAT_0052245c)[param_1 * 7 + param_2] = DAT_0059f154;
  FUN_00476c44(param_1,param_2,uVar2);
  while (*(int *)(&DAT_006534fc + param_1 * 4) == 2) {
    FUN_00477f9c();
  }
  iVar3 = *(int *)(&DAT_006534fc + param_1 * 4);
  if (iVar3 != 0) {
    if (iVar3 == 1) goto LAB_00407580;
    if (iVar3 == 3) {
      FUN_0040526c(param_1,param_2,8);
      local_8 = 1;
      goto LAB_00407580;
    }
    if (iVar3 != 4) goto LAB_00407580;
  }
  FUN_0040526c(param_1,param_2,0xfffffff8);
LAB_00407580:
  FUN_004767f0(param_1,0);
  return local_8;
}

