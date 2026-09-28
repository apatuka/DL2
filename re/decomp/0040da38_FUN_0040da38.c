// FUN_0040da38 @ 0040da38 size=64 sig=undefined FUN_0040da38() cc=unknown
// callers: FUN_0040dbc4,FUN_0040b644,FUN_0040fe58
// callees: 

undefined4 FUN_0040da38(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  while (((iVar1 = *piVar3, iVar1 == 0 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01'))
         || (*(int *)(iVar1 + 0x48) != 0))) {
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    if (0xf < iVar2) {
      return 0;
    }
  }
  return *(undefined4 *)(iVar1 + 0x3c);
}

