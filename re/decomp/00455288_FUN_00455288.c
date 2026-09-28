// FUN_00455288 @ 00455288 size=276 sig=undefined FUN_00455288() cc=unknown
// callers: FUN_004556b0
// callees: FUN_004511a4

void FUN_00455288(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined *local_18;
  ushort *local_14;
  int local_c;
  int local_8;
  
  uVar1 = 0x8000;
  iVar5 = *(int *)(param_1 + 0x24) + -1;
  local_18 = &DAT_0057d820 + iVar5 * 0x48;
  for (; iVar5 <= *(int *)(param_1 + 0x24) + 1; iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_1 + 0x20) + -1;
    local_14 = (ushort *)(local_18 + iVar4 * 2 + 0x29a);
    for (; iVar4 <= *(int *)(param_1 + 0x20) + 1; iVar4 = iVar4 + 1) {
      iVar2 = FUN_004511a4(iVar4,iVar5);
      if ((iVar2 != 0) &&
         (((iVar4 != *(int *)(param_1 + 0x20) || (iVar5 != *(int *)(param_1 + 0x24))) &&
          (*local_14 < uVar1)))) {
        local_c = iVar5;
        local_8 = iVar4;
        uVar1 = *local_14;
      }
      local_14 = local_14 + 1;
    }
    local_18 = local_18 + 0x48;
  }
  if (uVar1 < 0x8000) {
    uVar3 = 0;
    if (local_c < *(int *)(param_1 + 0x24)) {
      uVar3 = 1;
    }
    else if (*(int *)(param_1 + 0x24) < local_c) {
      uVar3 = 4;
    }
    if (local_8 < *(int *)(param_1 + 0x20)) {
      uVar3 = uVar3 | 8;
    }
    else if (*(int *)(param_1 + 0x20) < local_8) {
      uVar3 = uVar3 | 2;
    }
    if (DAT_0057e248 == 2) {
      if (uVar3 == *(byte *)(param_1 + 0x30)) {
        *(int *)(param_1 + 0x20) = local_8;
        *(int *)(param_1 + 0x24) = local_c;
      }
      else {
        *(undefined *)(param_1 + 0x30) =
             (&DAT_004d0144)[uVar3 + (uint)*(byte *)(param_1 + 0x30) * 0xd];
      }
    }
    else {
      *(char *)(param_1 + 0x30) = (char)uVar3;
      *(int *)(param_1 + 0x20) = local_8;
      *(int *)(param_1 + 0x24) = local_c;
    }
  }
  return;
}

