// FUN_00496906 @ 00496906 size=63 sig=undefined FUN_00496906() cc=unknown
// callers: 
// callees: FUN_004968c8

int FUN_00496906(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  do {
    iVar1 = FUN_004968c8(param_1,iVar2 << 0x18 | param_2 & 0xffffff);
    if (iVar1 == 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  return 0;
}

