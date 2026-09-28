// FUN_00488c1c @ 00488c1c size=121 sig=undefined FUN_00488c1c() cc=unknown
// callers: FUN_004983ae,FUN_00495162,FUN_00498826,FUN_0049859f
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,WriteFile,FUN_004950da
// strings: \"Error writing to file, ref = %d, buff = %d, size = %d, (%s)\\r\\n\"|\"Write to file, ref = %d, buff = %d, size = %d\\r\\n\"

DWORD FUN_00488c1c(HANDLE param_1,LPCVOID param_2,DWORD param_3)

{
  BOOL BVar1;
  undefined4 uVar2;
  DWORD local_8;
  
  BVar1 = WriteFile(param_1,param_2,param_3,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_writing_to_file__ref____d__0051b437,param_1,param_2,param_3,uVar2);
    }
    local_8 = FUN_004888d0();
  }
  else if ((DAT_0051dcc4 & 8) != 0) {
    FUN_00495162(s_Write_to_file__ref____d__buff_____0051b475,param_1,param_2,local_8);
  }
  return local_8;
}

