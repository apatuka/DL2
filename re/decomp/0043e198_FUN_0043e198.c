// FUN_0043e198 @ 0043e198 size=148 sig=undefined FUN_0043e198() cc=unknown
// callers: FUN_0043e22c
// callees: FUN_00496e80,FUN_00498aab,FUN_00490ab3,FUN_00490796

void FUN_0043e198(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00490ab3(0,0x47414d49,0x31304d43,0,0);
  if (iVar1 != 0) {
    uVar2 = FUN_00498aab(iVar1,1);
    FUN_00496e80(uVar2,0x3f2,0,0,0,0,0xffffffff);
    FUN_00496e80(uVar2,0x3f2,0,1,0,0x18,0xffffffff);
    FUN_00496e80(uVar2,0x3f2,0,2,0x26e,0x18,0xffffffff);
    FUN_00496e80(uVar2,0x3f2,0,3,0,0x1a8,0xffffffff);
    FUN_00498aab(iVar1,0);
    FUN_00490796(iVar1,0);
  }
  return;
}

