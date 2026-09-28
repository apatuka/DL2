// FUN_00488f20 @ 00488f20 size=86 sig=undefined FUN_00488f20() cc=unknown
// callers: 
// callees: FUN_00495162,GetDriveTypeA
// strings: \"Error getting disk attribs %s\\r\\n\"

UINT FUN_00488f20(int param_1)

{
  UINT UVar1;
  LPCSTR lpRootPathName;
  undefined4 local_8;
  
  local_8 = (uint)CONCAT12(0x5c,CONCAT11(0x3a,(char)param_1 + '@'));
  if (param_1 == 0) {
    lpRootPathName = (LPCSTR)0x0;
  }
  else {
    lpRootPathName = (LPCSTR)&local_8;
  }
  UVar1 = GetDriveTypeA(lpRootPathName);
  if ((UVar1 == 0) && ((DAT_0051dcc4 & 1) != 0)) {
    FUN_00495162(s_Error_getting_disk_attribs__s_0051b5d0,&local_8);
  }
  return UVar1;
}

