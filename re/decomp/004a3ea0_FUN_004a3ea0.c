// FUN_004a3ea0 @ 004a3ea0 size=142 sig=undefined FUN_004a3ea0() cc=unknown
// callers: FUN_004a43da,FUN_004a3f2e
// callees: FUN_0049eb44,FUN_004989de,FUN_004a16fc,FUN_004a17f6,FUN_0049e3ab,FUN_00490796,FUN_004a3e49,FUN_004a18a9

undefined4 FUN_004a3ea0(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x1c) == 4) {
    if (*(int *)(param_2 + 0x50) != 0) {
      FUN_00490796(*(undefined4 *)(param_2 + 0x50),0);
      *(undefined4 *)(param_2 + 0x50) = 0;
    }
  }
  else if (*(int *)(param_2 + 0x1c) == 5) {
    FUN_0049e3ab(param_2);
  }
  FUN_004a3e49(param_1,param_2);
  FUN_004a16fc(param_2);
  FUN_004a18a9(param_2 + 0x34);
  FUN_004a18a9(param_2 + 0x100);
  FUN_004a17f6(param_1,param_2);
  FUN_0049eb44(param_1,param_2,2,0x3d,0x81,0);
  if (*(int *)(param_2 + 100) != 0) {
    FUN_004989de(*(undefined4 *)(param_2 + 100));
    *(undefined4 *)(param_2 + 100) = 0;
  }
  return 1;
}

