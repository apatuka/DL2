// FUN_004751d0 @ 004751d0 size=88 sig=undefined FUN_004751d0() cc=unknown
// callers: FUN_004782ec
// callees: sprintf,FUN_0042836c,FUN_00475198
// strings: \"Session #%d disconnected.\"|\"Player Disconnected\"

void FUN_004751d0(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined1 local_44 [64];
  
  uVar1 = *(ushort *)(param_1 + 0x1a);
  sprintf(local_44,PTR_s_Session___d_disconnected__00509be4,(uint)uVar1);
  FUN_0042836c(s_Player_Disconnected_004dbeb0,local_44,4,0,0);
  iVar2 = DAT_004d5a58;
  if (DAT_004d5a58 == DAT_0058f1f4) {
    iVar2 = uVar1 - 1;
  }
  if (-1 < iVar2) {
    FUN_00475198(iVar2);
  }
  return;
}

