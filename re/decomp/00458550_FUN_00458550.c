// FUN_00458550 @ 00458550 size=122 sig=undefined FUN_00458550() cc=unknown
// callers: FUN_0047549c,FUN_0047526c,FUN_00458434,FUN_00474cc4
// callees: CGNetPlayer_BroadcastMessageGuaranteed,CGNetPlayer_SendMessageGuaranteed

undefined4 FUN_00458550(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == 0) {
    if ((DAT_00583858 == 1) || (param_3 != 0)) {
      iVar1 = CGNetPlayer_BroadcastMessageGuaranteed(DAT_004d170c,param_1,0x5c);
      if (iVar1 < 0) {
        return 0xffffffff;
      }
    }
    else {
      if (DAT_004d1714 == 0) {
        return 0xffffffff;
      }
      iVar1 = CGNetPlayer_SendMessageGuaranteed(DAT_004d170c,DAT_004d1714,param_1,0x5c);
      if (iVar1 < 0) {
        return 0xffffffff;
      }
    }
  }
  else {
    iVar1 = CGNetPlayer_SendMessageGuaranteed(DAT_004d170c,param_2,param_1,0x5c);
    if (iVar1 < 0) {
      return 0xffffffff;
    }
  }
  return 0;
}

