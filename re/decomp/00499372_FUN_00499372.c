// FUN_00499372 @ 00499372 size=254 sig=undefined FUN_00499372() cc=unknown
// callers: 
// callees: FUN_0048fe90,FUN_00488ba3,FUN_0049935c,FUN_0048d07b,FUN_00490680,FUN_004989cf,FUN_00488c95,FUN_0049063b,FUN_004994ed

int FUN_00499372(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar4 = 1;
  if (param_5 == 2) {
    if (*(int *)(param_4 + 0x1c) != 0) {
      FUN_0048d07b(*(undefined4 *)(param_4 + 0x1c));
      FUN_004989cf(*(undefined4 *)(param_4 + 0x1c));
      FUN_0048fe90(param_4);
    }
  }
  else if ((param_5 == 3) || (param_5 == 5)) {
    local_8 = *(undefined4 *)(param_4 + 0x18);
    iVar3 = *(int *)(param_4 + 0x14);
    iVar1 = FUN_00490680(param_1);
    iVar4 = param_4;
    if (((iVar1 != -1) &&
        ((iVar2 = FUN_00488c95(iVar1,iVar3,0), -1 < iVar2 &&
         (iVar2 = FUN_00488ba3(iVar1,&local_c,4), iVar2 == 4)))) &&
       ((iVar2 = FUN_0049935c(local_c), iVar2 == 0 ||
        ((iVar1 = FUN_0049063b(param_1,1), iVar1 != -1 &&
         (iVar3 = FUN_00488c95(iVar1,iVar3 + 4,0), 0 < iVar3)))))) {
      local_18 = 2;
      local_10 = local_8;
      local_14 = iVar1;
      iVar3 = FUN_004994ed(&local_18,4,local_c,param_3,0);
      if (iVar3 != 0) {
        *(ushort *)(iVar3 + 0x28) = *(ushort *)(iVar3 + 0x28) | 8;
        FUN_0048fe90(param_4);
        *(int *)(param_4 + 0x1c) = iVar3;
      }
    }
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}

