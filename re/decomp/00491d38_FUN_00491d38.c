// FUN_00491d38 @ 00491d38 size=187 sig=undefined FUN_00491d38() cc=unknown
// callers: FUN_0048468c,FUN_004a2078,FUN_004639f4,FUN_00491898,FUN_0042de68
// callees: FUN_0048f7f1,FUN_0049b268

int FUN_00491d38(int param_1)

{
  undefined4 uVar1;
  
  if (DAT_0051dc20 != 0) {
    FUN_0048f7f1(param_1,DAT_0051dc20,*(short *)(param_1 + 2) * 4 + 8);
    if (DAT_0051dc24 != 0) {
      FUN_0048f7f1(param_1,DAT_0051dc24,*(short *)(param_1 + 2) * 4 + 8);
      *(byte *)(DAT_0051dc24 + 0x407) = *(byte *)(DAT_0051dc24 + 0x407) | 1;
    }
    if (DAT_0051bddc == 0) {
      if (DAT_0065e5a8 == 0x10) {
        uVar1 = 1;
        if (DAT_0065e5ac != 2) {
          uVar1 = 2;
        }
        FUN_0049b268(DAT_0051dc20,uVar1);
      }
    }
    else if (*(int *)(DAT_0051bddc + 0xc) == 0x10) {
      uVar1 = 1;
      if (*(short *)(DAT_0051bddc + 0x26) != 2) {
        uVar1 = 2;
      }
      FUN_0049b268(DAT_0051dc20,uVar1);
    }
  }
  return DAT_0051dc20;
}

