// FUN_00482a8c @ 00482a8c size=55 sig=undefined FUN_00482a8c() cc=unknown
// callers: FUN_00412f10,FUN_00412e94
// callees: FUN_00482964,FUN_00489c3e,FUN_00482d3c

undefined4 FUN_00482a8c(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = FUN_00482964(DAT_00657e40);
  if (iVar1 < 0) {
    return 0xffffffff;
  }
  puVar2 = &DAT_00657e40;
  puVar3 = &DAT_00657e20;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00482d3c();
  FUN_00489c3e();
  return 0;
}

