// NetReceiveCapsule @ 00457f7c size=342 sig=undefined NetReceiveCapsule() cc=unknown
// callers: FUN_00477f9c
// callees: memcpy,CGNetMessage_GetBuffer,NetPlayerDisconnect,FUN_00457e14,FUN_004418ec,CGNetMessage_GetInfo
// strings: \"NetReceiveCapsule\"

/* auto-named from string evidence: NetReceiveCapsule */

undefined8 NetReceiveCapsule(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  if ((DAT_004d1718 == 0) || (DAT_004d170c == 0)) {
    iVar1 = 0;
  }
  else if (DAT_004d1710 == 0) {
    iVar1 = FUN_00457e14();
    if (iVar1 == 0) {
      iVar1 = CGNetMessage_GetInfo(DAT_004d1710,&local_c);
      if (iVar1 == 3) {
        DAT_004d1710 = 0;
        iVar1 = NetPlayerDisconnect(local_c);
      }
      else {
        uVar2 = CGNetMessage_GetBuffer(DAT_004d1710,&local_10);
        iVar1 = FUN_004418ec(s_NetReceiveCapsule_004d1767,uVar2);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          memcpy(iVar1,local_10,uVar2);
          iVar3 = CGNetMessage_GetInfo(DAT_004d1710,&local_c);
          if (iVar3 < 0) {
            *(undefined4 *)(iVar1 + 4) = 0;
          }
          else {
            *(undefined4 *)(iVar1 + 4) = local_c;
          }
          DAT_004d1710 = 0;
        }
      }
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = CGNetMessage_GetInfo(DAT_004d1710,&local_c);
    if (iVar1 == 3) {
      DAT_004d1710 = 0;
      iVar1 = NetPlayerDisconnect(local_c);
    }
    else {
      uVar2 = CGNetMessage_GetBuffer(DAT_004d1710,&local_10);
      iVar1 = FUN_004418ec(s_NetReceiveCapsule_004d1767,uVar2);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        memcpy(iVar1,local_10,uVar2);
        iVar3 = CGNetMessage_GetInfo(DAT_004d1710,&local_c);
        if (iVar3 < 0) {
          *(undefined4 *)(iVar1 + 4) = 0;
        }
        else {
          *(undefined4 *)(iVar1 + 4) = local_c;
        }
        DAT_004d1710 = 0;
      }
    }
  }
  return CONCAT44(local_c,iVar1);
}

