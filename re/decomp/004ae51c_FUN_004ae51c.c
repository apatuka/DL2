// FUN_004ae51c @ 004ae51c size=42 sig=undefined FUN_004ae51c() cc=unknown
// callers: FUN_004afbe4
// callees: 

undefined4 FUN_004ae51c(int *param_1)

{
  if (*param_1 == 4) {
    param_1[6] = 0;
    param_1[7] = 0;
    return 1;
  }
  if (*param_1 == 5) {
    return 1;
  }
  return 0;
}

