// FUN_00460330 @ 00460330 size=686 sig=undefined FUN_00460330() cc=unknown
// callers: FUN_004618e8
// callees: FUN_004750c4,memset,ReadFile

undefined4 FUN_00460330(HANDLE param_1)

{
  int iVar1;
  BOOL BVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined2 auStackY_5ad50 [182256];
  undefined4 *local_30;
  undefined4 *local_2c;
  undefined2 *local_28;
  undefined2 *local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  int local_18;
  int local_14;
  int local_10;
  DWORD local_c;
  int local_8;
  
  iVar1 = 0x5a;
  do {
    local_8 = iVar1;
    iVar1 = local_8 + -1;
  } while (local_8 + -1 != 0);
  memset();
  BVar2 = ReadFile(param_1,&local_8,4,&local_c,(LPOVERLAPPED)0x0);
  if (BVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if ((DAT_00583da4 == 0) || (DAT_00583da4 == 1)) {
      memset();
      BVar2 = ReadFile(param_1,auStackY_5ad50,local_8 * 0x136,&local_c,(LPOVERLAPPED)0x0);
      if (BVar2 == 0) {
        return 0;
      }
      puVar8 = auStackY_5ad50;
      local_14 = 0;
      puVar6 = &DAT_005f0410;
      do {
        local_20 = (undefined4 *)(puVar6 + 0xc);
        *puVar6 = *puVar8;
        puVar9 = puVar6 + 0x16;
        puVar6[1] = puVar8[1];
        *(undefined1 *)(puVar6 + 2) = *(undefined1 *)(puVar8 + 2);
        *(undefined1 *)((int)puVar6 + 5) = *(undefined1 *)((int)puVar8 + 5);
        *(undefined1 *)(puVar6 + 3) = *(undefined1 *)(puVar8 + 3);
        *(undefined1 *)((int)puVar6 + 7) = *(undefined1 *)((int)puVar8 + 7);
        puVar6[4] = puVar8[4];
        puVar6[5] = puVar8[5];
        puVar6[6] = puVar8[6];
        *(undefined1 *)(puVar6 + 7) = *(undefined1 *)(puVar8 + 7);
        *(undefined1 *)((int)puVar6 + 0xf) = *(undefined1 *)((int)puVar8 + 0xf);
        puVar6[8] = puVar8[8];
        puVar6[9] = puVar8[9];
        puVar6[10] = puVar8[10];
        puVar6[0xb] = puVar8[0xb];
        *(undefined4 *)(puVar6 + 0x8d) = *(undefined4 *)(puVar8 + 0x97);
        *(undefined4 *)(puVar6 + 0x8f) = *(undefined4 *)(puVar8 + 0x99);
        local_10 = 0;
        local_28 = puVar6 + 0x1b;
        local_24 = puVar8 + 0x1b;
        local_1c = (undefined4 *)(puVar8 + 0xc);
        puVar4 = puVar8 + 0x16;
        do {
          *local_20 = *local_1c;
          *(undefined1 *)puVar9 = *(undefined1 *)puVar4;
          if (local_10 < 4) {
            *(undefined1 *)((int)puVar9 + 5) = *(undefined1 *)((int)puVar4 + 5);
            *local_28 = *local_24;
          }
          local_10 = local_10 + 1;
          local_28 = local_28 + 1;
          local_24 = local_24 + 1;
          puVar9 = (undefined2 *)((int)puVar9 + 1);
          puVar4 = (undefined2 *)((int)puVar4 + 1);
          local_20 = local_20 + 1;
          local_1c = local_1c + 1;
        } while (local_10 < 5);
        local_10 = 0;
        local_30 = (undefined4 *)(puVar6 + 0x1f);
        local_2c = (undefined4 *)(puVar8 + 0x1f);
        do {
          *local_30 = *local_2c;
          local_18 = 0;
          puVar5 = local_2c;
          puVar7 = local_30;
          do {
            puVar7 = puVar7 + 0xb;
            puVar5 = puVar5 + 0xb;
            *puVar7 = *puVar5;
            local_18 = local_18 + 1;
          } while (local_18 < 4);
          local_10 = local_10 + 1;
          local_30 = local_30 + 1;
          local_2c = local_2c + 1;
        } while (local_10 < 0xb);
        local_14 = local_14 + 1;
        puVar6 = puVar6 + 0x91;
        puVar8 = puVar8 + 0x9b;
      } while (local_14 < 0x4b0);
    }
    else {
      BVar2 = ReadFile(param_1,&DAT_005f0410,local_8 * 0x122,&local_c,(LPOVERLAPPED)0x0);
      if (BVar2 == 0) {
        return 0;
      }
    }
    for (puVar8 = &DAT_005f0410; puVar8 < &DAT_005f0410 + local_8 * 0x91; puVar8 = puVar8 + 0x91) {
      if (*(int *)(puVar8 + 0x8d) != 0) {
        uVar3 = FUN_004750c4();
        *(undefined4 *)(puVar8 + 0x8d) = uVar3;
      }
      if (*(int *)(puVar8 + 0x8f) != 0) {
        uVar3 = FUN_004750c4();
        *(undefined4 *)(puVar8 + 0x8f) = uVar3;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

