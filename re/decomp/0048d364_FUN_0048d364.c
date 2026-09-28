// FUN_0048d364 @ 0048d364 size=45 sig=undefined FUN_0048d364() cc=unknown
// callers: FUN_0048d391,FUN_0048d54f
// callees: FUN_00498a5c,FUN_004989ed

void FUN_0048d364(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x3c)) {
    if (*(int *)(param_1 + 0x3c) != 0) {
      FUN_004989ed(*(undefined4 *)(param_1 + 0x3c));
    }
    FUN_00498a5c(param_2);
    *(int *)(param_1 + 0x3c) = param_2;
  }
  return;
}

