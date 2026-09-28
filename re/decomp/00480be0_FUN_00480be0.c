// FUN_00480be0 @ 00480be0 size=407 sig=undefined FUN_00480be0() cc=unknown
// callers: FUN_00480d78
// callees: FUN_0044ba40,FUN_00444f20,FUN_0044d1a4,FUN_00444b74,FUN_0047e2fc,FUN_0044ba18,FUN_00445040

int FUN_00480be0(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (*(char *)(DAT_00657de0 + 0x20) == -1) {
    local_8 = 1;
  }
  else {
    local_8 = (int)(char)(&DAT_0059f162)[*(char *)(DAT_00657de0 + 0x20) * 0x2d8];
  }
  local_8 = local_8 + 0x62;
  if ((&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32] == '\x02') {
    param_3 = param_3 + 0x32;
    param_4 = param_4 + 0x19;
  }
  if ((*(ushort *)(&DAT_005a4512 + *(char *)(param_1 + 7) * 0x34 + *(short *)(param_1 + 8) * 0xadc)
      & 0xf00) == 0x200) {
    iVar1 = FUN_0044d1a4(&DAT_005a43d0 + *(short *)(param_1 + 8) * 0xadc,0x14,0);
    FUN_0047e2fc(&param_3,&param_4,iVar1 - *(char *)(param_1 + 7));
  }
  local_c = FUN_0044ba18(param_1);
  iVar1 = FUN_0044ba40(param_1);
  local_10 = 0;
  if (local_c < iVar1) {
    local_14 = iVar1 - local_c;
    if (param_5 < iVar1 - local_c) {
      piVar2 = &param_5;
    }
    else {
      piVar2 = &local_14;
    }
    local_10 = *piVar2;
  }
  for (iVar1 = 0; iVar1 < local_c + local_10; iVar1 = iVar1 + 1) {
    iVar3 = FUN_00444f20(local_8,(iVar1 % 5) * 6 + param_3 + (iVar1 / 5) * -6,
                         param_4 + (iVar1 % 5) * -3 + (iVar1 / 5) * -3,0);
    if (iVar3 != 0) {
      FUN_00444b74(iVar3,param_2);
      if (iVar1 < local_c) {
        FUN_00445040(iVar3,0,1);
        param_2 = param_2 + -1;
      }
      else {
        FUN_00445040(iVar3,1,1);
        param_2 = param_2 + -1;
      }
    }
  }
  return local_10;
}

