// FUN_004ad1a4 @ 004ad1a4 size=26 sig=undefined FUN_004ad1a4() cc=unknown
// callers: fclose
// callees: FUN_004acd5c,DeleteFileA

undefined4 FUN_004ad1a4(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = DeleteFileA(param_1);
  if (BVar1 == 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_004acd5c();
  }
  return uVar2;
}

