// FUN_00441e18 @ 00441e18 size=158 sig=undefined FUN_00441e18() cc=unknown
// callers: FUN_00441e18,FUN_00441eb8
// callees: FUN_00441e18

void FUN_00441e18(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  ushort *local_8;
  
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x2000 << ((byte)param_2 & 0x1f);
  iVar5 = 0;
  local_8 = (ushort *)(param_1 + 0x890);
  do {
    uVar3 = *local_8;
    for (iVar4 = 0; (uVar3 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
      if ((uVar3 & 1) != 0) {
        iVar1 = iVar5 * 0x10 + iVar4;
        iVar2 = iVar1 * 0xadc;
        if (((((0x2000 << ((byte)param_2 & 0x1f) & (&DAT_005a43ec)[iVar1 * 0x2b7]) == 0) &&
             ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)) &&
            ((&DAT_005a43f1)[iVar2] != '\0')) &&
           (*(char *)(param_1 + 0x20) == (&DAT_005a43f0)[iVar2])) {
          FUN_00441e18(&DAT_005a43d0 + iVar2,param_2);
        }
      }
      uVar3 = (short)uVar3 >> 1;
    }
    iVar5 = iVar5 + 1;
    local_8 = local_8 + 1;
  } while (iVar5 < 7);
  return;
}

