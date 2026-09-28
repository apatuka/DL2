// FUN_0045b8a8 @ 0045b8a8 size=61 sig=undefined FUN_0045b8a8() cc=unknown
// callers: FUN_0045be7c,FUN_0045bc10
// callees: FUN_00415588,FUN_00413fe4

void FUN_0045b8a8(int param_1)

{
  if (DAT_004d5aa0 == '\0') {
    FUN_00415588(param_1);
  }
  else {
    DAT_006534c0 = param_1 * 0x34 + DAT_00657de0 + 0x140;
    FUN_00413fe4();
  }
  return;
}

