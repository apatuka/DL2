// FUN_00430abc @ 00430abc size=69 sig=undefined FUN_00430abc() cc=unknown
// callers: FUN_00468394,FUN_0047361c,FUN_0043be98
// callees: FUN_00430348,FUN_004302e8,FUN_00436098,FUN_00449dec,FUN_004360ec,FUN_00436064,FUN_0043044c,FUN_00430410

int FUN_00430abc(void)

{
  int iVar1;
  
  if (DAT_004d5aa0 != '\0') {
    FUN_00436098();
    FUN_00436064();
  }
  FUN_00430348();
  FUN_004302e8();
  do {
    iVar1 = FUN_0043044c();
  } while (iVar1 == 0);
  FUN_00430410();
  if (DAT_004d5aa0 != '\0') {
    FUN_004360ec();
    FUN_00449dec();
  }
  return iVar1;
}

