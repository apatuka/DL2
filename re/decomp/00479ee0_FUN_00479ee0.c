// FUN_00479ee0 @ 00479ee0 size=174 sig=undefined FUN_00479ee0() cc=unknown
// callers: FUN_004782ec
// callees: sprintf,FUN_00478fec,FUN_004aa518,FUN_00427f30,DebugMessage
// strings: \"Error Saving Block\"|\"Receiving Game Data\\r%d%% complete\"

void FUN_00479ee0(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 local_54 [80];
  
  if (DAT_004dc310 != 0) {
    uVar2 = (uint)*(ushort *)(param_1 + 0x1a) << 8 | (uint)*(ushort *)(param_1 + 0x1c);
    FUN_00478fec(&DAT_00653a4c,&DAT_0065363c,uVar2);
    iVar1 = FUN_004aa518(&DAT_0065363c,1,uVar2,DAT_004dc310);
    if (iVar1 == 0) {
      DebugMessage(s_Error_Saving_Block_004dc38e);
    }
    DAT_006535fc = DAT_006535fc + uVar2;
    DAT_00653638 = 0;
    if (DAT_004d59b4 == 0x24) {
      sprintf(local_54,PTR_s_Receiving_Game_Data__d___complet_00509c38,
              (DAT_006535fc * 100) / DAT_006535f8);
      FUN_00427f30(local_54);
    }
  }
  return;
}

