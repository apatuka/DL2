// FUN_0043694c @ 0043694c size=43 sig=undefined FUN_0043694c() cc=unknown
// callers: FUN_0046903c,FUN_004680e4,FUN_004680ac
// callees: FUN_0043644c,FUN_00436864,FUN_00436418

int FUN_0043694c(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0043644c(param_1);
  if (iVar1 == 0) {
    iVar1 = 0x11;
  }
  else {
    FUN_00436418();
    do {
      iVar1 = FUN_00436864();
    } while (iVar1 == 0);
  }
  return iVar1;
}

