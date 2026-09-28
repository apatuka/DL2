// FUN_004888ec @ 004888ec size=172 sig=undefined FUN_004888ec() cc=unknown
// callers: FUN_0048f8e8,FUN_0049063b,FUN_00488f76,FUN_004952f0,FUN_00495162,FUN_0048fe0b,FUN_00490bca
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,CreateFileA,FUN_004950da
// strings: \"Opened, %s\\r\\n\"

HANDLE FUN_004888ec(LPCSTR param_1,uint param_2)

{
  HANDLE pvVar1;
  undefined4 uVar2;
  DWORD dwDesiredAccess;
  DWORD dwShareMode;
  
  dwShareMode = 0;
  if ((param_2 & 0x7fff) == 0) {
    dwDesiredAccess = 0x80000000;
    dwShareMode = 1;
  }
  else if ((param_2 & 0x7fff) == 1) {
    dwDesiredAccess = 0x40000000;
  }
  else {
    dwDesiredAccess = 0xc0000000;
  }
  pvVar1 = CreateFileA(param_1,dwDesiredAccess,dwShareMode,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                       (HANDLE)0x0);
  if (pvVar1 == (HANDLE)0xffffffff) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s__Error_opening___s___s__0051b2a4 + 1,param_1,uVar2);
    }
  }
  else if ((DAT_0051dcc4 & 2) != 0) {
    FUN_00495162(s_Opened___s_0051b2be,param_1);
  }
  return pvVar1;
}

