// FUN_00488e1b @ 00488e1b size=71 sig=undefined FUN_00488e1b() cc=unknown
// callers: 
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,SetCurrentDirectoryA,FUN_004950da
// strings: \"Error setting the default dir to %s, (%s)\\r\\n\"

undefined4 FUN_00488e1b(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = SetCurrentDirectoryA(param_1);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_setting_the_default_dir_to_0051b577,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

