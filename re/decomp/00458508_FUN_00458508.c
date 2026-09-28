// FUN_00458508 @ 00458508 size=71 sig=undefined FUN_00458508() cc=unknown
// callers: FUN_00468800
// callees: FUN_0042836c,CGNetService_ConnectToIPAddress
// strings: \"Your version of DirectX is not supported by the Matching Service. Make sure you're running the most recent version, then try again.\"|\"Network Error\"

undefined4 FUN_00458508(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = CGNetService_ConnectToIPAddress(DAT_00583b74,param_1);
  if (iVar1 == -0x85) {
    FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_Your_version_of_DirectX_is_not_s_005092ec,4,0,0)
    ;
    uVar2 = 0;
  }
  else if (iVar1 < 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

