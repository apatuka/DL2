// FUN_00474fa0 @ 00474fa0 size=78 sig=undefined FUN_00474fa0() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00474f5c

int FUN_00474fa0(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  pcVar1 = &DAT_0059f161;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    if ((*pcVar1 != '\0') && (pcVar1[7] == '\0')) {
      iVar3 = 1;
    }
    pcVar1 = pcVar1 + 0x2d8;
  }
  if (iVar3 != 0) {
    FUN_00474f5c((int)*(short *)(param_1 + 0x16),*(undefined2 *)(param_1 + 0x18));
  }
  return iVar3;
}

