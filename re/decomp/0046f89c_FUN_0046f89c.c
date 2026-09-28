// FUN_0046f89c @ 0046f89c size=46 sig=undefined FUN_0046f89c() cc=unknown
// callers: FUN_004474b0,FUN_0045c67c,FUN_0046b818,FUN_0046f938,FUN_0046ac44
// callees: qsort

void FUN_0046f89c(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_005904dc;
  do {
    *piVar2 = iVar1;
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x230);
  qsort(&DAT_005904dc,0x230,4,FUN_0046f85c);
  return;
}

