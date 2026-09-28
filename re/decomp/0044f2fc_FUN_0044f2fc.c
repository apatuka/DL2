// FUN_0044f2fc @ 0044f2fc size=244 sig=undefined FUN_0044f2fc() cc=unknown
// callers: FUN_0044f3f0
// callees: FUN_00447a40

void FUN_0044f2fc(int param_1,short param_2)

{
  undefined2 uVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  ushort *local_c;
  int local_8;
  
  for (iVar4 = *(int *)(param_1 + 0x76); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x54)) {
    if (*(char *)(iVar4 + 0x25) == '\x0e') {
      *(short *)(iVar4 + 0x28) = *(short *)(iVar4 + 0x28) + param_2;
      if (100 < *(short *)(iVar4 + 0x28)) {
        *(undefined2 *)(iVar4 + 0x28) = 100;
      }
      uVar1 = FUN_00447a40((int)*(short *)(iVar4 + 0x28));
      *(undefined2 *)(iVar4 + 0x2a) = uVar1;
    }
  }
  local_8 = 0;
  local_c = (ushort *)(param_1 + 0x890);
  do {
    uVar3 = *local_c;
    for (iVar4 = 0; (uVar3 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
      if (((uVar3 & 1) != 0) &&
         ((iVar2 = (local_8 * 0x10 + iVar4) * 0xadc, (&DAT_005a43f1)[iVar2] == '\0' &&
          ((&DAT_005a43f0)[iVar2] == *(char *)(param_1 + 0x20))))) {
        for (iVar2 = *(int *)(&DAT_005a4446 + iVar2); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
          if (*(char *)(iVar2 + 0x25) == '\x0e') {
            *(short *)(iVar2 + 0x28) = *(short *)(iVar2 + 0x28) + param_2;
            if (100 < *(short *)(iVar2 + 0x28)) {
              *(undefined2 *)(iVar2 + 0x28) = 100;
            }
            uVar1 = FUN_00447a40((int)*(short *)(iVar2 + 0x28));
            *(undefined2 *)(iVar2 + 0x2a) = uVar1;
          }
        }
      }
      uVar3 = (short)uVar3 >> 1;
    }
    local_8 = local_8 + 1;
    local_c = local_c + 1;
  } while (local_8 < 7);
  return;
}

