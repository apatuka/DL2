// FUN_0044d284 @ 0044d284 size=115 sig=undefined FUN_0044d284() cc=unknown
// callers: FUN_004669d8
// callees: 

undefined4 FUN_0044d284(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ushort *local_8;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    iVar4 = 0;
    local_8 = (ushort *)(param_1 + 0x890);
    do {
      uVar1 = *local_8;
      for (iVar3 = 0; (uVar1 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
        if (((uVar1 & 1) != 0) &&
           (((iVar2 = (iVar4 * 0x10 + iVar3) * 0xadc, (&DAT_005a444e)[iVar2] != '\0' &&
             ((&DAT_005a43f1)[iVar2] != '\0')) &&
            ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)))) {
          return 1;
        }
        uVar1 = (short)uVar1 >> 1;
      }
      iVar4 = iVar4 + 1;
      local_8 = local_8 + 1;
    } while (iVar4 < 7);
  }
  return 0;
}

