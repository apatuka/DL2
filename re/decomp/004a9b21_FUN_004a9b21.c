// FUN_004a9b21 @ 004a9b21 size=44 sig=undefined FUN_004a9b21() cc=unknown
// callers: FUN_004a73f0
// callees: 

void FUN_004a9b21(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined2 in_FS;
  
  piVar1 = (int *)segment(in_FS,0);
  puVar2 = (undefined4 *)*piVar1;
  if (param_1 == puVar2) {
    puVar2 = (undefined4 *)segment(in_FS,0);
    *puVar2 = *param_1;
  }
  else {
    for (; puVar2 != (undefined4 *)0xffffffff; puVar2 = (undefined4 *)*puVar2) {
      if ((undefined4 *)*puVar2 == param_1) {
        *puVar2 = *param_1;
        return;
      }
    }
  }
  return;
}

