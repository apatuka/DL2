// FUN_00465f84 @ 00465f84 size=68 sig=undefined FUN_00465f84() cc=unknown
// callers: FUN_00465fc8,FUN_00466014
// callees: 

int FUN_00465f84(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = (undefined4 *)(param_1 + 0x80);
  while( true ) {
    if (*(char *)(param_1 + 0x7e) <= iVar2) {
      return -1;
    }
    if ((param_2 == *(char *)*puVar1) && (((char *)*puVar1)[1] == param_3)) break;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  }
  return iVar2;
}

