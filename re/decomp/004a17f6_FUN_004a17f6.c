// FUN_004a17f6 @ 004a17f6 size=63 sig=undefined FUN_004a17f6() cc=unknown
// callers: FUN_004a4025,FUN_004a3ea0,FUN_004a1835
// callees: FUN_00490796

void FUN_004a17f6(int param_1,int param_2)

{
  if (param_1 != 0) {
    if (param_2 == 0) {
      FUN_00490796(*(undefined4 *)(param_1 + 0x50),1);
      *(undefined4 *)(param_1 + 0x50) = 0;
    }
    else {
      FUN_00490796(*(undefined4 *)(param_2 + 0xe4),1);
      *(undefined4 *)(param_2 + 0xe4) = 0;
    }
  }
  return;
}

