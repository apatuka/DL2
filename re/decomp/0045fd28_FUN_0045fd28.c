// FUN_0045fd28 @ 0045fd28 size=299 sig=undefined FUN_0045fd28() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile

BOOL FUN_0045fd28(HANDLE param_1)

{
  BOOL BVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 local_6d0 [434];
  undefined2 local_36c [428];
  undefined2 *local_14;
  undefined2 *local_10;
  int local_c;
  DWORD local_8;
  
  if (DAT_00583da8 < 0x23) {
    if (DAT_00583da4 < 1) {
      BVar1 = ReadFile(param_1,local_36c,0x356,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
    }
    else {
      BVar1 = ReadFile(param_1,local_6d0,0x364,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
    }
    local_c = 0;
    local_14 = local_36c;
    local_10 = &DAT_00559e00;
    puVar2 = local_6d0;
    do {
      iVar5 = 0;
      puVar4 = local_10;
      puVar3 = puVar2;
      puVar6 = local_14;
      do {
        if (DAT_00583da4 < 1) {
          *puVar4 = *puVar6;
        }
        else {
          *puVar4 = *puVar3;
        }
        iVar5 = iVar5 + 1;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar5 < 7);
      local_c = local_c + 1;
      local_14 = local_14 + 7;
      local_10 = local_10 + 7;
      puVar2 = puVar2 + 7;
    } while (local_c < 0x3e);
    iVar5 = 0;
    puVar4 = &DAT_0055a156;
    puVar2 = &DAT_004fc8dc;
    do {
      if (DAT_00583da4 < 1) {
        *puVar4 = *puVar2;
      }
      iVar5 = iVar5 + 1;
      puVar4[7] = puVar2[8];
      puVar3 = puVar2 + 0x10;
      puVar2 = puVar2 + 1;
      puVar4[0xe] = *puVar3;
      puVar4 = puVar4 + 1;
    } while (iVar5 < 7);
    BVar1 = 1;
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_00559e00,0x380,&local_8,(LPOVERLAPPED)0x0);
  }
  return BVar1;
}

