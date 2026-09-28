// FUN_00488998 @ 00488998 size=113 sig=undefined FUN_00488998() cc=unknown
// callers: FUN_00495162,FUN_00498826
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,CreateFileA,FUN_004950da
// strings: \"Error creating, %s (%s)\\r\\n\"|\"Created and opened, %s ref = %d\\r\\n\"

HANDLE FUN_00488998(LPCSTR param_1)

{
  HANDLE pvVar1;
  undefined4 uVar2;
  
  pvVar1 = CreateFileA(param_1,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  if (pvVar1 == (HANDLE)0xffffffff) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_creating___s___s__0051b2cb,param_1,uVar2);
    }
  }
  else if ((DAT_0051dcc4 & 2) != 0) {
    FUN_00495162(s_Created_and_opened___s_ref____d_0051b2e5,param_1,pvVar1);
  }
  return pvVar1;
}

