// FUN_00490d98 @ 00490d98 size=161 sig=undefined FUN_00490d98() cc=unknown
// callers: InitCYGame
// callees: FUN_00490122,FUN_00495162,FUN_00498ba9
// strings: \"CYLib Manager inited, max libraries: %d, locked lib headers: %d\\r\\n\"

undefined4 FUN_00490d98(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  DAT_0051daf8 = (undefined2 *)FUN_00498ba9(param_1 * 0x10a + 4);
  if (DAT_0051daf8 == (undefined2 *)0x0) {
    uVar1 = 0;
  }
  else {
    *DAT_0051daf8 = 0;
    DAT_0051daf8[1] = (short)param_1;
    DAT_0065eba8 = 0;
    DAT_0065ebac = 0;
    FUN_00490122(0x454c4954,FUN_004a52db);
    FUN_00490122(0x474c4954,FUN_004a54e5);
    FUN_00490122(0x47414d49,FUN_00496748);
    DAT_0051dafc = param_2;
    if ((DAT_0051dcc4 & 0x10) != 0) {
      FUN_00495162(s_CYLib_Manager_inited__max_librar_0051dbc7,param_1,param_2);
    }
    uVar1 = 1;
  }
  return uVar1;
}

