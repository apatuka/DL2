// FUN_00441d60 @ 00441d60 size=184 sig=undefined FUN_00441d60() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00441d60(char *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort *local_14;
  undefined4 local_8;
  
  piVar2 = param_2;
  local_8 = 0;
  do {
    iVar1 = *param_2;
    iVar6 = 0;
    local_14 = (ushort *)(iVar1 + 0x890);
    do {
      uVar3 = *local_14;
      for (iVar5 = 0; (uVar3 != 0 && (iVar5 < 0x10)); iVar5 = iVar5 + 1) {
        if (((uVar3 & 1) != 0) &&
           (iVar4 = (iVar6 * 0x10 + iVar5) * 0xadc, (&DAT_005a43f1)[iVar4] != '\0')) {
          if ((&DAT_005a43f0)[iVar4] == -1) {
            *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 0x200;
            local_8 = 1;
          }
          if ((&DAT_005a43f0)[iVar4] != *param_1) {
            *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 0x400;
          }
        }
        uVar3 = (short)uVar3 >> 1;
      }
      iVar6 = iVar6 + 1;
      local_14 = local_14 + 1;
    } while (iVar6 < 7);
    param_2 = (int *)param_2[1];
  } while (param_2 != piVar2);
  return local_8;
}

