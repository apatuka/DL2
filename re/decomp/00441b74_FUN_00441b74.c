// FUN_00441b74 @ 00441b74 size=127 sig=undefined FUN_00441b74() cc=unknown
// callers: 
// callees: 

int FUN_00441b74(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ushort *local_c;
  int local_8;
  
  local_8 = 0;
  local_c = (ushort *)(param_2 + 0x890);
  do {
    uVar1 = *local_c;
    for (iVar3 = 0; (uVar1 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
      if ((uVar1 & 1) != 0) {
        iVar2 = (local_8 * 0x10 + iVar3) * 0xadc;
        iVar4 = (int)(char)(&DAT_005a43f0)[iVar2];
        if (((iVar4 != -1) && (iVar4 != param_1)) && ((&DAT_005a4436)[param_1 + iVar2] != '\0')) {
          return iVar4;
        }
      }
      uVar1 = (short)uVar1 >> 1;
    }
    local_8 = local_8 + 1;
    local_c = local_c + 1;
    if (6 < local_8) {
      return -1;
    }
  } while( true );
}

