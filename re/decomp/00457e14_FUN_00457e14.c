// FUN_00457e14 @ 00457e14 size=233 sig=undefined FUN_00457e14() cc=unknown
// callers: NetReceiveCapsule,SpecialBroadcast,BroadcastDirect,FUN_004779c0,BroadcastText
// callees: CGNetMessage_GetBuffer,CGNetPlayer_GetMessage,CGNetMessage_GetInfo

undefined4 FUN_00457e14(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_c;
  int local_8;
  int local_4;
  
  if ((DAT_004d1718 == 0) || (DAT_004d170c == 0)) {
    uVar1 = 1;
  }
  else if (DAT_004d1710 == 0) {
    iVar2 = CGNetPlayer_GetMessage(DAT_004d170c,&local_c);
    while (-1 < iVar2) {
      iVar2 = CGNetMessage_GetInfo(local_c,&local_8);
      if ((iVar2 == 3) &&
         ((DAT_00583858 == 1 || ((DAT_00583858 == 0 && (local_8 == DAT_004d1714)))))) {
        DAT_004d1710 = local_c;
        return 0;
      }
      if (((iVar2 == 1) && (iVar2 = CGNetMessage_GetBuffer(local_c,&local_4), iVar2 == 0x5c)) &&
         ((*(char *)(local_4 + 2) != -1 || ((*(char *)(local_4 + 2) == -1 && (DAT_00583858 == 1)))))
         ) {
        DAT_004d1710 = local_c;
        return 0;
      }
      iVar2 = CGNetPlayer_GetMessage(DAT_004d170c,&local_c);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

