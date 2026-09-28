// FUN_00488b0f @ 00488b0f size=74 sig=undefined FUN_00488b0f() cc=unknown
// callers: 
// callees: FUN_004950d0,GetFileAttributesA,FUN_004888d0,FUN_00495162,FUN_004950da
// strings: \"Error getting file attribs, %s, (%s)\\r\\n\"

DWORD FUN_00488b0f(LPCSTR param_1)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_getting_file_attribs___s____0051b378,param_1,uVar2);
    }
    DVar1 = 0xffffffff;
  }
  return DVar1;
}

