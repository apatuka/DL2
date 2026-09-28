// FUN_004934e0 @ 004934e0 size=66 sig=undefined FUN_004934e0() cc=unknown
// callers: FUN_004994ed
// callees: FUN_004a6b00,FUN_004893dd

int FUN_004934e0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_8 [4];
  
  FUN_004893dd(param_1,local_8);
  iVar2 = 0;
  do {
    iVar1 = FUN_004a6b00(local_8,&DAT_0051dc44 + iVar2 * 4);
    if (iVar1 == 0) {
      return iVar2 + 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 6);
  return 0;
}

