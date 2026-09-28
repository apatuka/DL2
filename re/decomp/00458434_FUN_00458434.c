// FUN_00458434 @ 00458434 size=210 sig=undefined FUN_00458434() cc=unknown
// callers: FUN_00468c94
// callees: FUN_00458550,CGNetSession_CreatePlayer,CGNetSession_Join,FUN_00458640
// strings: \"Deadlock 2 Player\"

undefined4 FUN_00458434(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_5c;
  undefined4 local_56;
  undefined4 local_8;
  
  if (DAT_00583858 == 0) {
    if (param_1 < 0x14) {
      if ((&DAT_0058389c)[param_1 * 0x20] == '\0') {
        uVar1 = 0;
      }
      else {
        DAT_004d1708 = (&DAT_00583b1c)[param_1];
        iVar2 = CGNetSession_Join(DAT_004d1708);
        if (iVar2 < 0) {
          uVar1 = 0;
        }
        else {
          iVar2 = CGNetSession_CreatePlayer(DAT_004d1708,&DAT_004d170c,s_Deadlock_2_Player_004d1779)
          ;
          if (iVar2 < 0) {
            uVar1 = 0;
          }
          else {
            iVar2 = FUN_00458640(&local_8);
            if (iVar2 == 0) {
              DAT_004d1714 = 0;
            }
            else {
              DAT_004d1714 = local_8;
            }
            local_64 = 0;
            local_63 = 0;
            local_62 = 0xff;
            local_5c = 9;
            local_56 = 0x5c;
            DAT_004d16f8 = 0;
            iVar2 = FUN_00458550(&local_64,0,0);
            if (iVar2 == -1) {
              uVar1 = 0;
            }
            else {
              uVar1 = 1;
            }
          }
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

