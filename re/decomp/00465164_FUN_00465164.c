// FUN_00465164 @ 00465164 size=323 sig=undefined FUN_00465164() cc=unknown
// callers: 
// callees: Rectangle,FUN_00464b90,FUN_00464f80,GetStockObject,SelectObject

void FUN_00465164(int param_1,int param_2,int param_3,int param_4)

{
  HDC hdc;
  HGDIOBJ pvVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int local_24;
  int local_20;
  int local_1c;
  HGDIOBJ local_18;
  HGDIOBJ local_14;
  int local_10;
  int local_c;
  int local_8;
  
  hdc = *(HDC *)(param_1 + 0x18);
  iVar2 = *(int *)(param_1 + 0x1c);
  local_c = *(int *)(param_1 + 0x20);
  local_8 = *(int *)(param_1 + 0x24);
  local_10 = *(int *)(param_1 + 0x28);
  pvVar1 = GetStockObject(1);
  local_18 = SelectObject(hdc,pvVar1);
  pvVar1 = GetStockObject(7);
  local_14 = SelectObject(hdc,pvVar1);
  Rectangle(hdc,iVar2,local_c,local_8,local_10);
  if (param_2 != 0) {
    iVar2 = local_8 - iVar2;
    uVar4 = iVar2 - param_3;
    iVar5 = (int)uVar4 >> 1;
    if (iVar5 < 0) {
      iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
    }
    uVar4 = (local_10 - local_c) - param_4;
    local_1c = (int)uVar4 >> 1;
    if (local_1c < 0) {
      local_1c = local_1c + (uint)((uVar4 & 1) != 0);
    }
    if (iVar5 < 2) {
      iVar5 = 2;
    }
    if (local_1c < 2) {
      local_1c = 2;
    }
    local_20 = iVar2 + -4;
    if (param_3 < local_20) {
      piVar3 = &param_3;
    }
    else {
      piVar3 = &local_20;
    }
    param_3 = *piVar3;
    local_24 = (local_10 - local_c) + -4;
    if (param_3 < local_24) {
      piVar3 = &param_3;
    }
    else {
      piVar3 = &local_24;
    }
    param_4 = *piVar3;
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + iVar5;
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + local_1c;
    FUN_00464b90(hdc,param_1 + 0x1c,param_2,param_3,param_4);
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) - iVar5;
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) - local_1c;
  }
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
  *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + -1;
  FUN_00464f80(hdc,param_1 + 0x1c,*(uint *)(param_1 + 0x10) & 1);
  SelectObject(hdc,local_14);
  SelectObject(hdc,local_18);
  return;
}

