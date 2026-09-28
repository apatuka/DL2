// FUN_0048a145 @ 0048a145 size=353 sig=undefined FUN_0048a145() cc=unknown
// callers: FUN_0048a53c,FUN_0048a8c3
// callees: FUN_0048f992,ReleaseMutex,FUN_0048fb67,WaitForSingleObject,FUN_0048f774

int FUN_0048a145(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  uint uVar1;
  DWORD DVar2;
  int iVar3;
  int iVar4;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = 0;
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  if (param_1 == 0) {
    local_1c = 0;
  }
  else {
    DVar2 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar2 == 0xffffffff) {
      local_1c = 0;
    }
    else {
      if (param_4 == 0) {
        local_18 = *(uint *)(param_1 + 8);
      }
      else {
        local_18 = FUN_0048fb67(param_4);
        if (*(uint *)(param_1 + 8) < local_18) {
          local_18 = *(uint *)(param_1 + 8);
        }
      }
      uVar1 = local_18;
      if ((-1 < (int)param_3) && (uVar1 = param_3, (int)local_18 < (int)param_3)) {
        uVar1 = local_18;
      }
      local_18 = uVar1;
      iVar4 = 0;
      do {
        iVar3 = (**(code **)(**(int **)(param_1 + 0x44) + 0x2c))
                          (*(int **)(param_1 + 0x44),param_2,local_18,&local_8,&local_10,&local_c,
                           &local_14,0);
        if (iVar3 != -0x7787ff6a) break;
        (**(code **)(**(int **)(param_1 + 0x44) + 0x50))(*(int **)(param_1 + 0x44));
        iVar4 = iVar4 + 1;
      } while (iVar4 < 2);
      if (iVar3 == 0) {
        if (local_10 != 0) {
          if (param_4 == 0) {
            local_20 = local_10;
            FUN_0048f774(local_8,local_10,0);
            local_24 = local_14;
            if (local_14 != 0) {
              FUN_0048f774(local_c,local_14,0);
            }
          }
          else {
            local_20 = FUN_0048f992(param_4,local_8,local_10);
            if (local_14 != 0) {
              local_24 = FUN_0048f992(param_4,local_c,local_14);
            }
          }
          local_1c = local_20 + local_24;
        }
        (**(code **)(**(int **)(param_1 + 0x44) + 0x4c))
                  (*(int **)(param_1 + 0x44),local_8,local_20,local_c,local_24);
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return local_1c;
}

