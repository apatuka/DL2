// FUN_0044890c @ 0044890c size=209 sig=undefined FUN_0044890c() cc=unknown
// callers: FUN_004489e0
// callees: 

undefined4 FUN_0044890c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  ushort *local_c;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x76);
  while( true ) {
    if (iVar2 == 0) {
      local_8 = 0;
      local_c = (ushort *)(param_1 + 0x890);
      do {
        uVar3 = *local_c;
        for (iVar2 = 0; (uVar3 != 0 && (iVar2 < 0x10)); iVar2 = iVar2 + 1) {
          if (((uVar3 & 1) != 0) &&
             ((iVar1 = (local_8 * 0x10 + iVar2) * 0xadc, (&DAT_005a43f1)[iVar1] == '\0' &&
              ((&DAT_005a43f0)[iVar1] == *(char *)(param_1 + 0x20))))) {
            for (iVar1 = *(int *)(&DAT_005a4446 + iVar1); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)
                ) {
              if ((*(char *)(iVar1 + 0x25) == '\x0e') && (*(short *)(iVar1 + 0x28) + param_2 < 100))
              {
                return 1;
              }
            }
          }
          uVar3 = (short)uVar3 >> 1;
        }
        local_8 = local_8 + 1;
        local_c = local_c + 1;
        if (6 < local_8) {
          return 0;
        }
      } while( true );
    }
    if ((*(char *)(iVar2 + 0x25) == '\x0e') && (*(short *)(iVar2 + 0x28) + param_2 < 100)) break;
    iVar2 = *(int *)(iVar2 + 0x54);
  }
  return 1;
}

