// FUN_00406dd8 @ 00406dd8 size=453 sig=undefined FUN_00406dd8() cc=unknown
// callers: FUN_004073a4,FUN_00406fa0,FUN_00407290
// callees: FUN_00476b58,FUN_004412d4,FUN_00406b1c,FUN_00406d10,FUN_00477f9c,FUN_0040526c,FUN_004767f0,FUN_00476c44,FUN_00441388

undefined4 FUN_00406dd8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_8;
  
  local_8 = 0;
  if (((&DAT_0059f161)[param_2 * 0x2d8] == '\0') ||
     (DAT_0059f154 - (&DAT_0052245c)[param_1 * 7 + param_2] < 5)) {
    return 0;
  }
  uVar3 = 0;
  iVar2 = FUN_00441388(param_1,param_2,1);
  if (((iVar2 == 0) && (iVar2 = FUN_00441388(param_1,param_2,2), iVar2 == 0)) &&
     (iVar2 = FUN_00406b1c(param_1,param_2,1,1), iVar2 != 0)) {
    uVar3 = 1;
  }
  iVar2 = FUN_00441388(param_1,param_2,2);
  if (((iVar2 == 0) && (uVar3 == 0)) && (iVar2 = FUN_00406b1c(param_1,param_2,2,1), iVar2 != 0)) {
    uVar3 = 2;
  }
  iVar2 = FUN_00441388(param_1,param_2,8);
  if ((iVar2 == 0) && (iVar2 = FUN_00406b1c(param_1,param_2,uVar3 | 8,1), iVar2 != 0)) {
    uVar3 = uVar3 | 8;
  }
  iVar2 = FUN_00441388(param_1,param_2,4);
  if ((iVar2 == 0) && (iVar2 = FUN_00406b1c(param_1,param_2,uVar3 | 4,1), iVar2 != 0)) {
    uVar3 = uVar3 | 4;
  }
  iVar2 = FUN_00441388(param_1,param_2,0x10);
  if (((iVar2 == 0) && (iVar2 = FUN_004412d4(param_1,param_2,0xe), iVar2 != 0)) &&
     (iVar2 = FUN_00406b1c(param_1,param_2,0x10,1), iVar2 != 0)) {
    uVar3 = 0x10;
  }
  iVar2 = FUN_00406d10(param_1,param_2,uVar3);
  if (iVar2 == 0) {
    return 0;
  }
  FUN_004767f0(param_1,2);
  (&DAT_0052245c)[param_1 * 7 + param_2] = DAT_0059f154;
  FUN_00476c44(param_1,param_2,iVar2);
  while (*(int *)(&DAT_006534fc + param_1 * 4) == 2) {
    FUN_00477f9c();
  }
  iVar1 = *(int *)(&DAT_006534fc + param_1 * 4);
  if (iVar1 != 0) {
    if (iVar1 == 1) goto LAB_00406f89;
    if (iVar1 == 3) {
      FUN_00476b58(param_1,param_2,iVar2);
      FUN_0040526c(param_1,param_2,8);
      local_8 = 1;
      goto LAB_00406f89;
    }
    if (iVar1 != 4) goto LAB_00406f89;
  }
  FUN_0040526c(param_1,param_2,0xfffffff8);
LAB_00406f89:
  FUN_004767f0(param_1,0);
  return local_8;
}

