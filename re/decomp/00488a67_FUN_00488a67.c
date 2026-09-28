// FUN_00488a67 @ 00488a67 size=71 sig=undefined FUN_00488a67() cc=unknown
// callers: FUN_00495241,FUN_004393e8
// callees: DeleteFileA,FUN_004950d0,FUN_004888d0,FUN_00495162,FUN_004950da
// strings: \"Error deleting file, %s, (%s)\\r\\n\"

undefined4 FUN_00488a67(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = DeleteFileA(param_1);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_deleting_file___s____s__0051b333,param_1,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

