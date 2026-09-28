// FUN_004ae26c @ 004ae26c size=103 sig=undefined FUN_004ae26c() cc=unknown
// callers: CheckSubTech,FUN_004956e2,FUN_0043044c,FUN_00497859,FUN_004957b5,FUN_0041287c,FUN_004371e4,FUN_00414004,FUN_004375f4,CheckSubRes,FUN_00471028,FUN_004ae2d4,CheckMoveStuff
// callees: FUN_004aff64

int FUN_004ae26c(char *param_1)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  bool bVar5;
  
  iVar4 = 0;
  do {
    pcVar3 = param_1;
    cVar2 = *pcVar3;
    param_1 = pcVar3 + 1;
    iVar1 = FUN_004aff64((int)cVar2);
  } while (iVar1 != 0);
  if ((cVar2 == '+') || (cVar2 == '-')) {
    bVar5 = cVar2 == '-';
    cVar2 = *param_1;
    param_1 = pcVar3 + 2;
  }
  else {
    bVar5 = false;
  }
  while (('/' < cVar2 && (cVar2 < ':'))) {
    iVar4 = iVar4 * 10 + (int)cVar2 + -0x30;
    cVar2 = *param_1;
    param_1 = param_1 + 1;
  }
  if (bVar5) {
    iVar4 = -iVar4;
  }
  return iVar4;
}

