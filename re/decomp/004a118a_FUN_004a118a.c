// FUN_004a118a @ 004a118a size=130 sig=undefined FUN_004a118a() cc=unknown
// callers: FUN_004a19b4,FUN_004a1eb4,FUN_004a120c,FUN_004a1607,FUN_004a3bd0
// callees: FUN_0049ea99

undefined4 FUN_004a118a(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_1 != 0) {
    if (param_4 == 0) {
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_2;
      *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3;
    }
    else {
      *(int *)(param_1 + 0xc) = param_2;
      *(int *)(param_1 + 0x10) = param_3;
    }
    if (((((*(uint *)(param_1 + 0x24) & 0x1f) == 4) && (*(int *)(param_1 + 0x38) != 0)) &&
        ((*(byte *)(*(int *)(param_1 + 0x38) + 0x28) & 1) != 0)) &&
       ((*(byte *)(*(int *)(param_1 + 0x38) + 0xb4) & 1) != 0)) {
      iVar1 = FUN_0049ea99(param_1);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x38) + 0xb8) + 0x60))
                (*(undefined4 *)(*(int *)(param_1 + 0x38) + 0xb8),
                 *(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc),
                 *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10),0,0);
    }
  }
  return 1;
}

