// FUN_004ac260 @ 004ac260 size=107 sig=undefined FUN_004ac260() cc=unknown
// callers: FUN_004ac2cc
// callees: memcpy,FUN_004a67a8

int FUN_004ac260(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = param_1 + param_2;
  iVar4 = param_1;
  iVar5 = param_1;
  while( true ) {
    uVar2 = FUN_004a67a8(iVar4,0xd,uVar1 - iVar4);
    if (uVar2 == 0) {
      uVar2 = uVar1;
    }
    iVar3 = uVar2 - iVar4;
    if (iVar5 != iVar4) {
      memcpy(iVar5,iVar4,iVar3);
    }
    if (uVar1 - 1 <= uVar2) break;
    iVar4 = uVar2 + 1;
    iVar5 = iVar5 + iVar3;
  }
  return (iVar5 - param_1) + iVar3;
}

