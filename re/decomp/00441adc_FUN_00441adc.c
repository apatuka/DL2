// FUN_00441adc @ 00441adc size=151 sig=undefined FUN_00441adc() cc=unknown
// callers: 
// callees: FUN_004412d4

int FUN_00441adc(int param_1,int param_2)

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
    for (iVar4 = 0; (uVar2 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
      if ((uVar2 & 1) != 0) {
        iVar3 = (local_8 * 0x10 + iVar4) * 0xadc;
        iVar1 = (int)(char)(&DAT_005a43f0)[iVar3];
        if ((((iVar1 != -1) && (iVar1 != param_1)) &&
            (iVar1 = FUN_004412d4(param_1,iVar1,2), iVar1 == 0)) &&
           ((&DAT_005a4436)[param_1 + iVar3] != '\0')) {
          return (int)(char)(&DAT_005a43f0)[iVar3];
        }
      }
      uVar2 = (short)uVar2 >> 1;
    }
    local_8 = local_8 + 1;
    local_c = local_c + 1;
    if (6 < local_8) {
      return -1;
    }
  } while( true );
}

