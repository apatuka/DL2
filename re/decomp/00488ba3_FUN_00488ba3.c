// FUN_00488ba3 @ 00488ba3 size=121 sig=undefined FUN_00488ba3() cc=unknown
// callers: FUN_0048f992,FUN_004906e3,FUN_00499372,FUN_0049028e,FUN_004952f0,FUN_0048fe0b
// callees: FUN_004950d0,FUN_004888d0,ReadFile,FUN_00495162,FUN_004950da
// strings: \"Error reading from file, ref = %d, buff = %d, size = %d, (%s)\\r\\n\"|\"Read from file, ref = %d, buff = %d, size = %d\\r\\n\"

DWORD FUN_00488ba3(HANDLE param_1,LPVOID param_2,DWORD param_3)

{
  BOOL BVar1;
  undefined4 uVar2;
  DWORD local_8;
  
  BVar1 = ReadFile(param_1,param_2,param_3,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_reading_from_file__ref_____0051b3c6,param_1,param_2,param_3,uVar2);
    }
    local_8 = FUN_004888d0();
  }
  else if ((DAT_0051dcc4 & 4) != 0) {
    FUN_00495162(s_Read_from_file__ref____d__buff___0051b406,param_1,param_2,local_8);
  }
  return local_8;
}

