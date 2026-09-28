// FUN_00488d7e @ 00488d7e size=85 sig=undefined FUN_00488d7e() cc=unknown
// callers: 
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,GetFullPathNameA,FUN_004950da
// strings: \"Error expanding path name %s, (%s)\\r\\n\"

undefined4 FUN_00488d7e(LPCSTR param_1,LPSTR param_2)

{
  DWORD DVar1;
  undefined4 uVar2;
  LPSTR local_8;
  
  DVar1 = GetFullPathNameA(param_1,0x104,param_2,&local_8);
  if (DVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_expanding_path_name__s_____0051b52c,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

