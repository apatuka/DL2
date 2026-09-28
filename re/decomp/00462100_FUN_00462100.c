// FUN_00462100 @ 00462100 size=518 sig=undefined FUN_00462100() cc=unknown
// callers: FUN_0045f828
// callees: ReadFile,memset

/* WARNING: Removing unreachable block (ram,0x0046226c) */
/* WARNING: Removing unreachable block (ram,0x0046212a) */
/* WARNING: Removing unreachable block (ram,0x004621e5) */
/* WARNING: Removing unreachable block (ram,0x00462275) */

undefined4 FUN_00462100(HANDLE param_1,LPVOID param_2,int param_3,int param_4)

{
  BOOL BVar1;
  ushort *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  int local_10;
  ushort local_a;
  DWORD local_8;
  
  if (param_4 < 4) {
    BVar1 = ReadFile(param_1,param_2,0x74,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    *(undefined4 *)((int)param_2 + 0x74) = 1;
    *(undefined4 *)((int)param_2 + 0x7c) = 0;
    puVar5 = (undefined1 *)((int)param_2 + 0x80);
    local_a = 0;
    local_10 = 0;
    puVar2 = (ushort *)((int)param_2 + 0x2a);
    puVar3 = (undefined4 *)((int)param_2 + 0x88);
    do {
      if ((int)(short)local_a < (int)(uint)*puVar2) {
        local_a = *puVar2;
      }
      *puVar5 = 2;
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
      local_10 = local_10 + 1;
      puVar5 = puVar5 + 1;
      puVar2 = puVar2 + 1;
    } while (local_10 < 8);
    memset((int)param_2 + 0xa4,0,3);
    *(int *)((int)param_2 + 0x78) = (int)(short)local_a;
    *(undefined4 *)((int)param_2 + 0xa8) = 1;
  }
  else if (param_3 < 3) {
    BVar1 = ReadFile(param_1,param_2,0x88,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    iVar4 = 0;
    puVar3 = (undefined4 *)((int)param_2 + 0x88);
    do {
      iVar4 = iVar4 + 1;
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    } while (iVar4 < 7);
    memset((int)param_2 + 0xa4,0,3);
    *(undefined4 *)((int)param_2 + 0xa8) = 1;
  }
  else if (param_3 < 9) {
    if (param_3 < 7) {
      iVar4 = 6;
    }
    else {
      iVar4 = 2;
    }
    BVar1 = ReadFile(param_1,param_2,0xac - iVar4,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    memset((int)param_2 + 0xa4,0,3);
    *(undefined4 *)((int)param_2 + 0xa8) = 1;
  }
  else {
    BVar1 = ReadFile(param_1,param_2,0xac,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
  }
  if (param_3 == 0) {
    iVar4 = 0;
    puVar5 = (undefined1 *)((int)param_2 + 0x80);
    do {
      *puVar5 = 2;
      if (iVar4 < *(int *)((int)param_2 + 0xc)) {
        *(byte *)((int)param_2 + 0x87) =
             *(byte *)((int)param_2 + 0x87) | '\x01' << ((byte)iVar4 & 0x1f);
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 7);
  }
  return 1;
}

