// FUN_00488c95 @ 00488c95 size=84 sig=undefined FUN_00488c95() cc=unknown
// callers: FUN_0048f8e8,FUN_0048fade,FUN_004906e3,FUN_00499372,FUN_0048fa92,FUN_004952f0,FUN_00495162,FUN_0049859f
// callees: FUN_004950d0,FUN_004888d0,SetFilePointer,FUN_00495162,FUN_004950da
// strings: \"Error seeking in file, ref = %d, pos = %d, mode = %d, (%s)\\r\\n\"

DWORD FUN_00488c95(HANDLE param_1,LONG param_2,DWORD param_3)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = SetFilePointer(param_1,param_2,(PLONG)0x0,param_3);
  if (DVar1 == 0xffffffff) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_seeking_in_file__ref____d__0051b4a5,param_1,param_2,param_3,uVar2);
    }
  }
  return DVar1;
}

