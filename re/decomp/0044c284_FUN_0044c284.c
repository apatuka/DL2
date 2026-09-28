// FUN_0044c284 @ 0044c284 size=57 sig=undefined FUN_0044c284() cc=unknown
// callers: FUN_0044c2c0,FUN_0045b448
// callees: 

undefined4 FUN_0044c284(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = (char *)(param_1 + 0x2c);
  while ((*pcVar2 == '\0' || ((0x100 << ((byte)iVar1 & 0x1f) & (int)*(short *)(param_1 + 2)) != 0)))
  {
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
    if (4 < iVar1) {
      return 1;
    }
  }
  return 0;
}

