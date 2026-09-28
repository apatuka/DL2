// FUN_004a26e8 @ 004a26e8 size=351 sig=undefined FUN_004a26e8() cc=unknown
// callers: FUN_0041e81c,FUN_004a2cb5,FUN_00427440,FUN_0042dbb8
// callees: FUN_0049eb44,FUN_0048d2e7,FUN_0049e2d5,FUN_0048d32c,FUN_00496a97,GetTickCount,FUN_0049eafa

void FUN_004a26e8(int param_1)

{
  int iVar1;
  DWORD DVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (*(int *)(param_1 + 0x3c) != 0) {
    FUN_0048d2e7(*(undefined4 *)(param_1 + 0x3c));
  }
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if ((*(byte *)(iVar1 + 0x29) & 1) == 0) {
        if ((*(int *)(iVar1 + 0x1c) == 5) && ((*(byte *)(iVar1 + 0x24) & 0x80) != 0)) {
          FUN_0049e2d5(iVar1,2);
        }
        else if ((((*(uint *)(iVar1 + 0x24) & 0x1f) == 4) &&
                 ((*(int *)(iVar1 + 0x38) != 0 &&
                  ((*(byte *)(*(int *)(iVar1 + 0x38) + 0x28) & 1) != 0)))) &&
                ((*(byte *)(*(int *)(iVar1 + 0x38) + 0xb4) & 1) != 0)) {
          (**(code **)(*(int *)(*(int *)(iVar1 + 0x38) + 0xb8) + 0x7c))
                    (*(undefined4 *)(*(int *)(iVar1 + 0x38) + 0xb8));
        }
      }
      else {
        DVar2 = GetTickCount();
        if (*(uint *)(iVar1 + 0x5c) < DVar2) {
          DVar2 = GetTickCount();
          *(DWORD *)(iVar1 + 0x5c) = DVar2 + *(int *)(iVar1 + 0x58);
          if ((((*(int *)(iVar1 + 0x40) == 0) ||
               (iVar3 = (**(code **)(iVar1 + 0x40))(iVar1,4,0,0), iVar3 == 0)) &&
              ((*(uint *)(iVar1 + 0x24) & 0x1f) == 2)) && (*(int *)(iVar1 + 0x38) != 0)) {
            uVar4 = FUN_0049eafa(iVar1);
            iVar3 = FUN_00496a97(**(undefined4 **)(iVar1 + 0x38),*(undefined4 *)(iVar1 + 0x54),uVar4
                                );
            if (iVar3 != 0) {
              FUN_0049eb44(param_1,iVar1,2,8,0,0);
              *(int *)(iVar1 + 0x50) = *(int *)(iVar1 + 0x50) + 1;
              if ((int)(uint)*(ushort *)(iVar3 + 0x1e) <= *(int *)(iVar1 + 0x50)) {
                *(undefined4 *)(iVar1 + 0x50) = 0;
              }
              FUN_0049eb44(param_1,iVar1,2,8,0,0);
            }
          }
        }
      }
    }
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    FUN_0048d32c();
  }
  return;
}

