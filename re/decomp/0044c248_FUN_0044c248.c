// FUN_0044c248 @ 0044c248 size=59 sig=undefined FUN_0044c248() cc=unknown
// callers: FUN_0044c2c0,FUN_0045b448
// callees: 

undefined4 FUN_0044c248(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x18);
  while ((*piVar2 == 0 || ((0x100 << ((byte)iVar1 & 0x1f) & (int)*(short *)(param_1 + 2)) != 0))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
    if (4 < iVar1) {
      return 1;
    }
  }
  return 0;
}

