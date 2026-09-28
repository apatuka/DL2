// FUN_004a191b @ 004a191b size=83 sig=undefined FUN_004a191b() cc=unknown
// callers: FUN_004a3533,FUN_004a19b4
// callees: 

void FUN_004a191b(int param_1,int param_2)

{
  *(int *)(param_1 + 0x60) = param_2;
  if (((((*(uint *)(param_1 + 0x24) & 0x1f) == 4) && (*(int *)(param_1 + 0x38) != 0)) &&
      ((*(byte *)(*(int *)(param_1 + 0x38) + 0x28) & 1) != 0)) &&
     ((*(byte *)(*(int *)(param_1 + 0x38) + 0xb4) & 1) != 0)) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x38) + 0xb8) + 0x70))
              (*(undefined4 *)(*(int *)(param_1 + 0x38) + 0xb8),param_2 == 1);
  }
  return;
}

