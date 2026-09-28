// FUN_00488b59 @ 00488b59 size=74 sig=undefined FUN_00488b59() cc=unknown
// callers: 
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,SetFileAttributesA,FUN_004950da
// strings: \"Error setting file attribs, %s, (%s)\\r\\n\"

undefined4 FUN_00488b59(LPCSTR param_1,DWORD param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = SetFileAttributesA(param_1,param_2);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_setting_file_attribs___s____0051b39f,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

