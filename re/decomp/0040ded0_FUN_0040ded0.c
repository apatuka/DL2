// FUN_0040ded0 @ 0040ded0 size=115 sig=undefined FUN_0040ded0() cc=unknown
// callers: FUN_0040df44,FUN_0040f974
// callees: 

undefined4 FUN_0040ded0(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *local_8;
  
  iVar5 = 0;
  local_8 = (ushort *)(param_2 + 0x890);
  do {
    uVar1 = *local_8;
    for (iVar4 = 0; (uVar1 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
      if (((uVar1 & 1) != 0) &&
         (((iVar2 = iVar5 * 0x10 + iVar4, iVar3 = iVar2 * 0xadc, (&DAT_005a43f1)[iVar3] != '\0' &&
           ((char)(&DAT_005a43f0)[iVar3] == param_1)) && ((&DAT_005a4400)[iVar2 * 0x56e] != 0)))) {
        return 1;
      }
      uVar1 = (short)uVar1 >> 1;
    }
    iVar5 = iVar5 + 1;
    local_8 = local_8 + 1;
    if (6 < iVar5) {
      return 0;
    }
  } while( true );
}

