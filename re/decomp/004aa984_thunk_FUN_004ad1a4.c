// thunk_FUN_004ad1a4 @ 004aa984 size=5 sig=undefined thunk_FUN_004ad1a4() cc=unknown
// callers: FUN_004657e0,GetHighScores,FUN_00412654,FUN_00467e58
// callees: 

undefined4 thunk_FUN_004ad1a4(LPCSTR param_1)

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

