// FUN_00488aae @ 00488aae size=97 sig=undefined FUN_00488aae() cc=unknown
// callers: FUN_00438b9c,ChCht,FUN_004397a0
// callees: FUN_004950d0,FUN_004888d0,CreateDirectoryA,FUN_00495162,FUN_004950da
// strings: \"Error creating directory, %s, (%s)\\r\\n\"

undefined4 FUN_00488aae(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  _SECURITY_ATTRIBUTES local_10;
  
  local_10.nLength = 0xc;
  local_10.lpSecurityDescriptor = (LPVOID)0x0;
  local_10.bInheritHandle = 0;
  BVar1 = CreateDirectoryA(param_1,&local_10);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_creating_directory___s_____0051b353,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

