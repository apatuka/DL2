// FUN_00472bf0 @ 00472bf0 size=175 sig=undefined FUN_00472bf0() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0047280c,FUN_00472974

void FUN_00472bf0(void)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_18 [4];
  int local_14 [2];
  
  iVar5 = 1;
  do {
    FUN_0047280c();
    do {
      bVar1 = false;
      for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar4 = puVar4 + 0x2b7) {
        if ((*(char *)(puVar4 + 8) != -1) &&
           (*(int *)((int)puVar4 + iVar5 * 4 + 0x3a) < *(int *)((int)puVar4 + iVar5 * 4 + 0xa7e))) {
          local_14[0] = *(int *)((int)puVar4 + iVar5 * 4 + 0xa7e) -
                        *(int *)((int)puVar4 + iVar5 * 4 + 0x3a);
          local_14[1] = 10;
          if (local_14[0] < 0xb) {
            piVar3 = local_14;
          }
          else {
            piVar3 = local_14 + 1;
          }
          iVar2 = FUN_00472974(puVar4,(int)*(char *)(puVar4 + 8),iVar5,*piVar3,1,local_18,local_18);
          if (iVar2 != -1) {
            bVar1 = true;
          }
        }
      }
    } while (bVar1);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0xb);
  return;
}

