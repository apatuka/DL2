// FUN_00488ce9 @ 00488ce9 size=71 sig=undefined FUN_00488ce9() cc=unknown
// callers: FUN_0048fb67
// callees: FUN_004950d0,GetFileSize,FUN_004888d0,FUN_00495162,FUN_004950da
// strings: \"Error getting file size, ref = %d, (%s)\\r\\n\"

DWORD FUN_00488ce9(HANDLE param_1)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = GetFileSize(param_1,(LPDWORD)0x0);
  if (DVar1 == 0xffffffff) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_getting_file_size__ref_____0051b4e2,param_1,uVar2);
    }
  }
  return DVar1;
}

