// FUN_00411990 @ 00411990 size=216 sig=undefined FUN_00411990() cc=unknown
// callers: FUN_00411c64,FUN_00411adc,FUN_00411d28
// callees: GetTickCount,free,FUN_004b02a8,FUN_004a6b48

undefined4 FUN_00411990(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  DWORD DVar3;
  int iVar4;
  
  if ((0 < *(int *)(param_1 + 0xc)) && (*(int *)(param_1 + 0xc) == *(int *)(param_1 + 0x10))) {
    iVar1 = *(int *)(param_1 + 4);
    iVar4 = iVar1;
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1a)) {
      if (*(uint *)(iVar1 + 0x12) < *(uint *)(iVar4 + 0x12)) {
        iVar4 = iVar1;
      }
    }
    if (iVar4 == 0) {
      return 0xffffffff;
    }
    if (*(int *)(iVar4 + 0x16) == 0) {
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(iVar4 + 0x1a);
    }
    else {
      *(undefined4 *)(*(int *)(iVar4 + 0x16) + 0x1a) = *(undefined4 *)(iVar4 + 0x1a);
    }
    if (*(int *)(iVar4 + 0x1a) != 0) {
      *(undefined4 *)(*(int *)(iVar4 + 0x1a) + 0x16) = *(undefined4 *)(iVar4 + 0x16);
    }
    if (*(int *)(iVar4 + 10) != 0) {
      free(*(int *)(iVar4 + 10));
    }
    free(iVar4);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
  }
  iVar1 = FUN_004b02a8(0x1e);
  if (iVar1 == 0) {
    uVar2 = 0xfffffffc;
  }
  else {
    FUN_004a6b48(iVar1,param_2,9);
    *(undefined1 *)(iVar1 + 9) = 0;
    *(undefined4 *)(iVar1 + 10) = param_3;
    *(undefined4 *)(iVar1 + 0xe) = param_4;
    DVar3 = GetTickCount();
    *(DWORD *)(iVar1 + 0x12) = DVar3;
    *(undefined4 *)(iVar1 + 0x16) = 0;
    *(undefined4 *)(iVar1 + 0x1a) = *(undefined4 *)(param_1 + 4);
    *(int *)(param_1 + 4) = iVar1;
    if (*(int *)(iVar1 + 0x1a) != 0) {
      *(int *)(*(int *)(iVar1 + 0x1a) + 0x16) = iVar1;
    }
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    uVar2 = 0;
  }
  return uVar2;
}

