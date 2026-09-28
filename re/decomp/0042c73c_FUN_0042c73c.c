// FUN_0042c73c @ 0042c73c size=88 sig=undefined FUN_0042c73c() cc=unknown
// callers: FUN_0042d3dc
// callees: FUN_0042c448,Timer_Init

undefined4 FUN_0042c73c(void)

{
  int iVar1;
  
  if (DAT_004bf910 != 0) {
    return 1;
  }
  iVar1 = Timer_Init(DAT_00557c48);
  if (iVar1 != 0) {
    FUN_0042c448();
    return 1;
  }
  DAT_004c5b74 = 0x9b;
  DAT_004c5b70 = 0x1aa;
  DAT_004c5b7c = 0x163;
  DAT_004c5b78 = 0x272;
  return 1;
}

