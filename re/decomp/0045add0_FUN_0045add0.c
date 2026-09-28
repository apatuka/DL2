// FUN_0045add0 @ 0045add0 size=47 sig=undefined FUN_0045add0() cc=unknown
// callers: WinMain,DumpGameOptions,FUN_004780e4,FUN_00486b74,FUN_0046e39c
// callees: 

int FUN_0045add0(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  pcVar1 = &DAT_0059f161;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    if ((*pcVar1 != '\0') && (*pcVar1 < '\x03')) {
      iVar3 = iVar3 + 1;
    }
    pcVar1 = pcVar1 + 0x2d8;
  }
  return iVar3;
}

