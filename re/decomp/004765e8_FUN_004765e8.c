// FUN_004765e8 @ 004765e8 size=128 sig=undefined FUN_004765e8() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_004723cc,FUN_00475048,memset
// strings: \"Error in Net Transfer Materials.\"

bool FUN_004765e8(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint local_30 [11];
  
  memset(local_30,0,0x2c);
  uVar1 = *(ushort *)(param_1 + 0x18);
  local_30[(short)(*(ushort *)(param_1 + 0x1a) & 0xff)] = (uint)*(ushort *)(param_1 + 0x1c);
  iVar2 = FUN_004723cc(&DAT_005a43d0 + ((int)(uint)uVar1 >> 8) * 0xadc,
                       &DAT_005a43d0 + (uVar1 & 0xff) * 0xadc,local_30);
  if (iVar2 == -1) {
    FUN_00475048(s_Error_in_Net_Transfer_Materials__004dc15c,param_1);
  }
  return iVar2 != -1;
}

