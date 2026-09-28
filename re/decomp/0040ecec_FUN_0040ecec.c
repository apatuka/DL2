// FUN_0040ecec @ 0040ecec size=221 sig=undefined FUN_0040ecec() cc=unknown
// callers: FUN_0040edcc
// callees: FindConstructionSite,FUN_00401440

undefined4 FUN_0040ecec(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  ushort *local_8;
  
  if ((((*(char *)(param_1 + 0x20) == *(char *)(param_2 + 8)) && (*(short *)(param_1 + 0x30) != 0))
      && (*(char *)(param_1 + 0x21) != '\0')) &&
     (iVar1 = FindConstructionSite(param_1,0x23), iVar1 != -1)) {
    if ((&DAT_004faf8d)[*(char *)(param_2 + 6) * 0x24] == '\x02') {
      iVar1 = 0;
      local_8 = (ushort *)(param_1 + 0x890);
      do {
        uVar3 = *local_8;
        for (iVar4 = 0; (uVar3 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
          if (((uVar3 & 1) != 0) &&
             ((iVar2 = (iVar1 * 0x10 + iVar4) * 0xadc, (&DAT_005a43f1)[iVar2] == '\0' &&
              (iVar2 = FUN_00401440(param_2,&DAT_005a43d0 + iVar2,0), iVar2 != 0)))) {
            return 1;
          }
          uVar3 = (short)uVar3 >> 1;
        }
        iVar1 = iVar1 + 1;
        local_8 = local_8 + 1;
      } while (iVar1 < 7);
    }
    else {
      iVar1 = FUN_00401440(param_2,param_1,0);
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  return 0;
}

