// FUN_00488e9d @ 00488e9d size=131 sig=undefined FUN_00488e9d() cc=unknown
// callers: 
// callees: FUN_004950d0,FUN_004888d0,FUN_00495162,GetDiskFreeSpaceA,FUN_004950da
// strings: \"Error getting disk space attribs %s , (%s)\\r\\n\"

int FUN_00488e9d(int param_1)

{
  LPCSTR lpRootPathName;
  BOOL BVar1;
  undefined4 uVar2;
  int iVar3;
  DWORD local_18;
  DWORD local_14;
  DWORD local_10;
  DWORD local_c;
  char local_8 [4];
  
  local_8[0] = (char)param_1 + '@';
  local_8[1] = 0x3a;
  local_8[2] = 0x5c;
  local_8[3] = 0;
  if (param_1 == 0) {
    lpRootPathName = (LPCSTR)0x0;
  }
  else {
    lpRootPathName = local_8;
  }
  BVar1 = GetDiskFreeSpaceA(lpRootPathName,&local_c,&local_10,&local_14,&local_18);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_getting_disk_space_attribs_0051b5a3,local_8,uVar2);
    }
    iVar3 = FUN_004888d0();
  }
  else {
    iVar3 = local_10 * local_c * local_14;
  }
  return iVar3;
}

