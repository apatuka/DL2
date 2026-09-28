// FUN_004606f4 @ 004606f4 size=225 sig=undefined FUN_004606f4() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile,memset,FUN_0047510c

undefined4 FUN_004606f4(HANDLE param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined2 *puVar5;
  int iVar6;
  DWORD local_c;
  int local_8;
  
  memset(&DAT_00645370,0,0xc940);
  BVar1 = ReadFile(param_1,&local_8,4,&local_c,(LPOVERLAPPED)0x0);
  if ((BVar1 != 0) &&
     (BVar1 = ReadFile(param_1,&DAT_00645370,local_8 * 0x5c,&local_c,(LPOVERLAPPED)0x0), BVar1 != 0)
     ) {
    for (puVar5 = &DAT_00645370; puVar5 < &DAT_00645370 + local_8 * 0x2e; puVar5 = puVar5 + 0x2e) {
      if (*(int *)(puVar5 + 0x2a) != 0) {
        uVar2 = FUN_0047510c(*(undefined4 *)(puVar5 + 0x2a));
        *(undefined4 *)(puVar5 + 0x2a) = uVar2;
      }
      if (*(int *)(puVar5 + 0x2c) != 0) {
        uVar2 = FUN_0047510c(*(undefined4 *)(puVar5 + 0x2c));
        *(undefined4 *)(puVar5 + 0x2c) = uVar2;
      }
      iVar6 = 0;
      piVar4 = (int *)(puVar5 + 0x24);
      do {
        if (*piVar4 != 0) {
          iVar3 = FUN_0047510c(*piVar4);
          *piVar4 = iVar3;
        }
        iVar6 = iVar6 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar6 < 3);
      *(undefined4 *)(puVar5 + 0x22) = 0;
      puVar5[0x1b] = 0;
    }
    return 1;
  }
  return 0;
}

