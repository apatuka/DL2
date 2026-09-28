// FUN_0048389c @ 0048389c size=53 sig=undefined FUN_0048389c() cc=unknown
// callers: FUN_00483f20,FUN_00483d58,FUN_00483a30
// callees: 

uint FUN_0048389c(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = 0;
  pcVar2 = &DAT_0059f162;
  do {
    if (*(short *)(&DAT_0055a102 + *pcVar2 * 2) != 0) {
      uVar3 = uVar3 | 1 << ((byte)iVar1 & 0x1f);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  } while (iVar1 < 7);
  return uVar3;
}

