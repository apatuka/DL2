// FUN_00488a09 @ 00488a09 size=94 sig=undefined FUN_00488a09() cc=unknown
// callers: FUN_00488f76,FUN_0048fbbf,FUN_004952f0,FUN_00495162,FUN_004906b5,FUN_0048fe0b,FUN_00498826,FUN_00489538
// callees: CloseHandle,FUN_004950d0,FUN_004888d0,FUN_00495162,FUN_004950da
// strings: \"Error closing file, %d, (%s)\\r\\n\"|\"Closed, %d\\r\\n\"

undefined4 FUN_00488a09(HANDLE param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = CloseHandle(param_1);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_closing_file___d____s__0051b307,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    if ((DAT_0051dcc4 & 2) != 0) {
      FUN_00495162(s_Closed___d_0051b326,param_1);
    }
    uVar2 = 0;
  }
  return uVar2;
}

