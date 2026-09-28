// FUN_00413250 @ 00413250 size=124 sig=undefined FUN_00413250() cc=unknown
// callers: 
// callees: FUN_00413348,PostMessageA,FUN_0048dc0d

void FUN_00413250(undefined4 param_1,int param_2,int param_3,int param_4)

{
  if (param_2 == 0x3bd) {
    if (*(char *)(param_3 + 0x3c) == '\0') {
      FUN_0048dc0d();
    }
    else {
      if (*(int *)(param_3 + 0x2a) < *(int *)(param_3 + 10)) {
        FUN_00413348(*(undefined4 *)(*(int *)(param_3 + 0xe) + *(int *)(param_3 + 0x2a) * 4),
                     *(undefined4 *)(param_3 + 0x1e),*(undefined4 *)(param_3 + 0x22),
                     *(undefined4 *)(param_3 + 0x26));
        *(int *)(param_3 + 0x2a) = *(int *)(param_3 + 0x2a) + 1;
      }
      if (*(int *)(param_4 + 0xc) == *(int *)(param_3 + 0x30)) {
        if (*(HWND *)(param_3 + 0x34) != (HWND)0x0) {
          PostMessageA(*(HWND *)(param_3 + 0x34),0x400,0,0);
          *(undefined4 *)(param_3 + 0x34) = 0;
        }
        *(undefined1 *)(param_3 + 0x3c) = 0;
      }
      FUN_0048dc0d();
    }
  }
  return;
}

