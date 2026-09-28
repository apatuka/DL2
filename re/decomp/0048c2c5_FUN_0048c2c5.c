// FUN_0048c2c5 @ 0048c2c5 size=303 sig=undefined FUN_0048c2c5() cc=unknown
// callers: FUN_0048c4eb,FUN_0048c662,FUN_0048c55b,FUN_0048c5c5,FUN_00411808,FUN_0048d205,FUN_0048c85e,FUN_0048cc08,FUN_004a52db,FUN_00463bcc,FUN_0048c434
// callees: FUN_00495162
// strings: \"Unable to lock offport: Error =      %#08x\\r\\n\"|\"FALSE\"|\"               Offport: Primary =    %s\\r\\n\"|\"                        Size =       %d, %d\\r\\n\"|\"                        Lock Count = %d, %d\\r\\n\"|\"Tried to lock a NULL offport\\r\\n\"

undefined4 FUN_0048c2c5(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    if ((DAT_0051dcc5 & 1) != 0) {
      FUN_00495162(s_Tried_to_lock_a_NULL_offport_0051c2aa);
    }
    uVar2 = 0;
  }
  else {
    if ((*(short *)((int)param_1 + 0x2a) == 0) && ((short)param_1[9] == 0)) {
      iVar1 = (**(code **)(*(int *)param_1[0x10] + 0x60))((int *)param_1[0x10]);
      if ((iVar1 != 0) &&
         (iVar1 = (**(code **)(*(int *)param_1[0x10] + 0x6c))((int *)param_1[0x10]), iVar1 != 0)) {
        return 0;
      }
      local_10 = 0;
      local_8 = param_1[2];
      local_14 = 0;
      local_c = param_1[1];
      param_1[0x11] = 0x6c;
      iVar1 = (**(code **)(*(int *)param_1[0x10] + 100))
                        ((int *)param_1[0x10],&local_14,param_1 + 0x11,1,0);
      if (iVar1 != 0) {
        if ((DAT_0051dcc5 & 1) != 0) {
          FUN_00495162(s_Unable_to_lock_offport__Error_____0051c1ec,iVar1);
          if ((*(byte *)(param_1 + 10) & 2) == 0) {
            pcVar3 = s_FALSE_0051c248;
          }
          else {
            pcVar3 = &DAT_0051c243;
          }
          FUN_00495162(s_Offport__Primary____s_0051c219,pcVar3);
          FUN_00495162(s_Size____d___d_0051c24e,param_1[1],param_1[2]);
          FUN_00495162(s_Lock_Count____d___d_0051c27c,(int)(short)param_1[9]);
        }
        return 0;
      }
      param_1[4] = param_1[0x15];
      *param_1 = param_1[4] * param_1[6] + (param_1[3] + 7 >> 3) * param_1[5] + param_1[0x1a];
    }
    *(short *)(param_1 + 9) = (short)param_1[9] + 1;
    uVar2 = 1;
  }
  return uVar2;
}

