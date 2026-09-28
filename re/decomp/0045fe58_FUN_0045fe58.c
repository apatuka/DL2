// FUN_0045fe58 @ 0045fe58 size=115 sig=undefined FUN_0045fe58() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_0045fe58(HANDLE param_1)

{
  undefined2 *puVar1;
  BOOL BVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18 [8];
  DWORD local_8;
  
  iVar5 = 0;
  while( true ) {
    local_1c = (&DAT_004fbbac)[iVar5 * 0x19];
    puVar4 = local_18;
    local_1a = (&DAT_004fbbae)[iVar5 * 0x19];
    iVar3 = 0;
    puVar1 = &DAT_004fbbb2 + iVar5 * 0x19;
    do {
      *puVar4 = *puVar1;
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar3 < 7);
    BVar2 = WriteFile(param_1,&local_1c,0x12,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) break;
    iVar5 = iVar5 + 1;
    if (0x2f < iVar5) {
      return 1;
    }
  }
  return 0;
}

