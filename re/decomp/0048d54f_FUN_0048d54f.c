// FUN_0048d54f @ 0048d54f size=117 sig=undefined FUN_0048d54f() cc=unknown
// callers: FUN_00413348
// callees: FUN_0048d364

void FUN_0048d54f(int param_1,int param_2)

{
  int iVar1;
  int *local_c;
  undefined4 local_8;
  
  if (((*(short *)(param_1 + 0x2a) == 0) && (*(short *)(param_2 + 0x2a) == 0)) &&
     (*(int *)(param_1 + 0x3c) != 0)) {
    iVar1 = (**(code **)(**(int **)(param_1 + 0x40) + 0x50))(*(int **)(param_1 + 0x40),&local_8);
    if (iVar1 == 0) {
      iVar1 = (**(code **)(**(int **)(param_2 + 0x40) + 0x50))(*(int **)(param_2 + 0x40),&local_c);
      if (iVar1 != 0) {
        local_c = (int *)0x0;
      }
      (**(code **)(**(int **)(param_2 + 0x40) + 0x7c))(*(int **)(param_2 + 0x40),local_8);
      if (local_c != (int *)0x0) {
        (**(code **)(*local_c + 8))(local_c);
      }
      FUN_0048d364(param_2,*(undefined4 *)(param_1 + 0x3c));
    }
  }
  return;
}

