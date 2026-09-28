// FUN_004916e9 @ 004916e9 size=95 sig=undefined FUN_004916e9() cc=unknown
// callers: FUN_0049185e
// callees: GlobalUnlock,FUN_0048d391,FUN_0048d76a,FUN_004996fb,GlobalLock

int FUN_004916e9(HGLOBAL param_1)

{
  short sVar1;
  short sVar2;
  LPVOID pvVar3;
  int iVar4;
  undefined4 uVar5;
  
  pvVar3 = GlobalLock(param_1);
  sVar1 = *(short *)((int)pvVar3 + 0x10);
  sVar2 = *(short *)((int)pvVar3 + 0x12);
  GlobalUnlock(param_1);
  iVar4 = FUN_004996fb((int)sVar1,(int)sVar2,8);
  if (iVar4 != 0) {
    *(HGLOBAL *)(iVar4 + 0xb8) = param_1;
    *(undefined4 *)(iVar4 + 0xb0) = 4;
    uVar5 = FUN_0048d76a(0x100,0);
    FUN_0048d391(iVar4,uVar5);
  }
  return iVar4;
}

