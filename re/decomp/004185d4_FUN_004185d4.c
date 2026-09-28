// FUN_004185d4 @ 004185d4 size=54 sig=undefined FUN_004185d4() cc=unknown
// callers: FUN_00419678
// callees: FUN_00418564,FUN_00417e48

void FUN_004185d4(void)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_00417e48();
  uVar1 = FUN_00418564((int)(char)PTR_DAT_004d5988[2],0);
  iVar2 = 0;
  do {
    if (iVar2 != (char)PTR_DAT_004d5988[2]) {
      uVar1 = FUN_00418564(iVar2,uVar1);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 7);
  return;
}

