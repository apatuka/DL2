// FUN_004132e0 @ 004132e0 size=27 sig=undefined FUN_004132e0() cc=unknown
// callers: FUN_00412584
// callees: free

void FUN_004132e0(int param_1,byte param_2)

{
  if ((param_1 != 0) && ((param_2 & 1) != 0)) {
    free(param_1);
  }
  return;
}

