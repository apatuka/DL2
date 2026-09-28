// FUN_0044d2f8 @ 0044d2f8 size=114 sig=undefined FUN_0044d2f8() cc=unknown
// callers: FindConstructionSite,FUN_0047d1e0,FUN_0044d600,FUN_00402df4,FUN_00427854
// callees: 

undefined4 FUN_0044d2f8(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ushort *local_8;
  
  iVar4 = 0;
  local_8 = (ushort *)(param_1 + 0x890);
  do {
    uVar1 = *local_8;
    for (iVar3 = 0; (uVar1 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
      if (((uVar1 & 1) != 0) &&
         (((iVar2 = (iVar4 * 0x10 + iVar3) * 0xadc, (&DAT_005a444e)[iVar2] != '\0' &&
           ((char)(&DAT_005a43f1)[iVar2] == param_2)) &&
          ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)))) {
        return 1;
      }
      uVar1 = (short)uVar1 >> 1;
    }
    iVar4 = iVar4 + 1;
    local_8 = local_8 + 1;
    if (6 < iVar4) {
      return 0;
    }
  } while( true );
}

