// FUN_00488dd3 @ 00488dd3 size=72 sig=undefined FUN_00488dd3() cc=unknown
// callers: 
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,GetCurrentDirectoryA,FUN_004950da
// strings: \"Error getting the default dir, (%s)\\r\\n\"

undefined4 FUN_00488dd3(LPSTR param_1)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = GetCurrentDirectoryA(0x104,param_1);
  if (DVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_getting_the_default_dir____0051b551,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

