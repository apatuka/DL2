// FUN_0040c668 @ 0040c668 size=36 sig=undefined FUN_0040c668() cc=unknown
// callers: FUN_00407594,FUN_0040e994,FUN_0040eb34
// callees: 

int FUN_0040c668(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    if (*piVar1 != 0) {
      return *piVar1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  return 0;
}

