// FUN_0049e3d7 @ 0049e3d7 size=163 sig=undefined FUN_0049e3d7() cc=unknown
// callers: FUN_004a2847
// callees: FUN_00491a2b,FUN_0049eb9f,FUN_00491ace,FUN_0049ddf8,FUN_0049f7c9,FUN_0049331e

undefined4 FUN_0049e3d7(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  local_8 = 0;
  if (((*(byte *)(param_1 + 0x24) & 0x80) != 0) && ((*(byte *)(param_1 + 0x2a) & 0x80) != 0)) {
    iVar1 = FUN_0049ddf8(param_1);
    if (iVar1 != 0) {
      FUN_00491a2b(0);
      iVar2 = FUN_0049eb9f(param_1,0);
      if (iVar2 != 0) {
        iVar2 = FUN_0049331e(iVar1,*param_2,param_2[1],&local_c);
        if (iVar2 != 0) {
          if ((*(byte *)(param_2 + 5) & 0x20) == 0) {
            if (*(int *)(iVar1 + 0x18) != local_c) {
              *(int *)(iVar1 + 0x18) = local_c;
              local_8 = 1;
            }
          }
          else if (*(int *)(iVar1 + 0x1c) != local_c) {
            *(int *)(iVar1 + 0x1c) = local_c;
            local_8 = 1;
          }
          if (local_8 != 0) {
            FUN_0049f7c9(param_1);
          }
        }
      }
      FUN_00491ace();
    }
  }
  return 1;
}

