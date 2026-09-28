// FUN_0040d768 @ 0040d768 size=157 sig=undefined FUN_0040d768() cc=unknown
// callers: FUN_0040d808
// callees: FUN_004726cc,FUN_004412d4

undefined4 FUN_0040d768(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  ushort *local_c;
  int local_8;
  
  local_8 = 0;
  local_c = (ushort *)(param_2 + 0x890);
  do {
    uVar2 = *local_c;
    for (iVar3 = 0; (uVar2 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
      if ((uVar2 & 1) != 0) {
        iVar4 = (local_8 * 0x10 + iVar3) * 0xadc;
        iVar1 = (int)(char)(&DAT_005a43f0)[iVar4];
        if ((((iVar1 == -1) || (iVar1 == param_3)) ||
            (iVar1 = FUN_004412d4(param_3,iVar1,2), iVar1 != 0)) &&
           (iVar1 = FUN_004726cc(param_1,&DAT_005a43d0 + iVar4,param_3), iVar1 < 2)) {
          return 1;
        }
      }
      uVar2 = (short)uVar2 >> 1;
    }
    local_8 = local_8 + 1;
    local_c = local_c + 1;
    if (6 < local_8) {
      return 0;
    }
  } while( true );
}

