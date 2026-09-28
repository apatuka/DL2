// FUN_004a1607 @ 004a1607 size=245 sig=undefined FUN_004a1607() cc=unknown
// callers: FUN_004a3533,FUN_004a196e
// callees: FUN_00490ab3,FUN_004a118a

bool FUN_004a1607(undefined4 param_1,int param_2,int param_3)

{
  uint *puVar1;
  undefined4 uVar2;
  bool bVar3;
  
  if (param_3 == 0) {
    bVar3 = true;
  }
  else {
    if ((*(uint *)(param_2 + 0x24) & 0x1f) == 4) {
      uVar2 = FUN_00490ab3(0,0x54434950,param_3,0,0x80000000);
      *(undefined4 *)(param_2 + 0x38) = uVar2;
      if (((*(int *)(param_2 + 0x38) != 0) &&
          ((*(byte *)(*(int *)(param_2 + 0x38) + 0x28) & 1) != 0)) &&
         ((*(byte *)(*(int *)(param_2 + 0x38) + 0xb4) & 1) != 0)) {
        (**(code **)(*(int *)(*(int *)(param_2 + 0x38) + 0xb8) + 0x70))
                  (*(undefined4 *)(*(int *)(param_2 + 0x38) + 0xb8),*(int *)(param_2 + 0x60) == 1);
        puVar1 = (uint *)(*(int *)(*(int *)(param_2 + 0x38) + 0xb8) + 0x14);
        *puVar1 = *puVar1 | 2;
        FUN_004a118a(param_2,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 0x10),1);
        (**(code **)(*(int *)(*(int *)(param_2 + 0x38) + 0xb8) + 0x80))
                  (*(undefined4 *)(*(int *)(param_2 + 0x38) + 0xb8));
      }
    }
    else if ((*(uint *)(param_2 + 0x24) & 0x1f) == 2) {
      uVar2 = FUN_00490ab3(0,0x47414d49,param_3,0,0x80000000);
      *(undefined4 *)(param_2 + 0x38) = uVar2;
    }
    if (*(int *)(param_2 + 0x38) != 0) {
      *(int *)(param_2 + 0x11c) = param_3;
    }
    bVar3 = *(int *)(param_2 + 0x38) != 0;
  }
  return bVar3;
}

