// FUN_004a32d7 @ 004a32d7 size=82 sig=undefined FUN_004a32d7() cc=unknown
// callers: FUN_004a3329
// callees: FUN_0048df75,FUN_004a2cb5,FUN_004a322d,FUN_0048dee3

int FUN_004a32d7(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  int local_8;
  
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x10;
  local_8 = in_ECX;
  do {
    iVar2 = FUN_0048df75();
    *(int *)(param_1 + 0x2c) = iVar2;
    if (iVar2 != 0) {
      FUN_0048dee3();
    }
    iVar2 = FUN_004a2cb5(param_1,&local_8);
    FUN_004a322d(param_1);
  } while (((iVar2 != 0) || (local_8 == 0)) || (*(int *)(param_1 + 100) != 0));
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  return local_8;
}

