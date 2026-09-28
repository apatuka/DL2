// FUN_0045fecc @ 0045fecc size=115 sig=undefined FUN_0045fecc() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile

undefined4 FUN_0045fecc(HANDLE param_1)

{
  BOOL BVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18 [8];
  DWORD local_8;
  
  iVar5 = 0;
  do {
    BVar1 = ReadFile(param_1,&local_1c,0x12,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      return 0;
    }
    (&DAT_004fbbac)[iVar5 * 0x19] = local_1c;
    puVar4 = &DAT_004fbbb2 + iVar5 * 0x19;
    (&DAT_004fbbae)[iVar5 * 0x19] = local_1a;
    puVar2 = local_18;
    iVar3 = 0;
    do {
      *puVar4 = *puVar2;
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < 7);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x30);
  return 1;
}

