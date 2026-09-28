// FUN_00488d30 @ 00488d30 size=78 sig=undefined FUN_00488d30() cc=unknown
// callers: FUN_00495241
// callees: FUN_004950d0,MoveFileA,FUN_004888d0,FUN_00495162,FUN_004950da
// strings: \"Error renaming %s to %s, (%s)\\r\\n\"

undefined4 FUN_00488d30(LPCSTR param_1,LPCSTR param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = MoveFileA(param_1,param_2);
  if (BVar1 == 0) {
    FUN_004888d0();
    if ((DAT_0051dcc4 & 1) != 0) {
      uVar2 = FUN_004950d0();
      uVar2 = FUN_004950da(uVar2);
      FUN_00495162(s_Error_renaming__s_to__s____s__0051b50c,param_1,param_2,uVar2);
    }
    uVar2 = FUN_004888d0();
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

