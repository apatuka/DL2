// FUN_00499470 @ 00499470 size=125 sig=undefined FUN_00499470() cc=unknown
// callers: FUN_004994ed
// callees: FUN_00495aa4,FUN_004996fb

int FUN_00499470(undefined4 param_1,undefined4 param_2,int param_3,byte param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 in_ECX;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_8;
  
  iVar3 = 0;
  local_8 = in_ECX;
  if (param_3 == 6) {
    local_8 = 3;
  }
  iVar1 = FUN_00495aa4(param_1,param_2,local_8,param_5,0);
  if (iVar1 != 0) {
    uVar2 = DAT_0065e5a8;
    if ((param_4 & 1) != 0) {
      uVar2 = 0xffffffff;
    }
    iVar3 = FUN_004996fb(*(undefined4 *)(iVar1 + 0x10),*(undefined4 *)(iVar1 + 0xc),uVar2);
    if (iVar3 == 0) {
      (**(code **)(iVar1 + 0x40))(iVar1);
    }
    else {
      *(int *)(iVar3 + 0xb8) = iVar1;
      *(undefined4 *)(iVar3 + 0xb4) = 1;
      *(int *)(iVar3 + 0xb0) = param_3;
      *(int *)(iVar1 + 0x18) = iVar3;
    }
  }
  return iVar3;
}

