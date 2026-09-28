// DisableMainInterface @ 0043c0e8 size=188 sig=undefined DisableMainInterface() cc=unknown
// callers: FUN_0042eff4,FUN_0042ee18,FUN_004493dc
// callees: DebugMessage,FUN_0048d2e7,FUN_00493784,FUN_004a3fcd,FUN_0049a9e7,FUN_00414ea4,FUN_0049a8ed,FUN_0048d32c,FUN_0043b7e4,FUN_0049a93f,FUN_004a3fa6
// strings: \"gpMainInterface NULL in DisableMainInterface()\"

/* auto-named from string evidence: DisableMainInterface */

void DisableMainInterface(char param_1)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_004c48a0 == 0) {
    DebugMessage(s_gpMainInterface_NULL_in_DisableM_004c48cf);
  }
  else {
    if ((param_1 != '\0') && ((*(byte *)(DAT_004c48a0 + 0x1c) & 8) == 0)) {
      FUN_0048d2e7(DAT_004d5c28);
      FUN_0049a8ed();
      local_14 = 0;
      local_10 = 0;
      local_8 = 0x1e0;
      local_c = 0x280;
      FUN_0049a9e7(&local_14);
      FUN_00414ea4(&local_14);
      FUN_00493784(0,0,0x280,0x1e0,2,0,1);
      FUN_0049a93f();
      FUN_0048d32c();
    }
    FUN_004a3fa6(DAT_004c48a0,(int)param_1);
    FUN_004a3fcd(DAT_004c48a0,(int)param_1);
    if (param_1 != '\0') {
      FUN_0043b7e4();
    }
  }
  return;
}

