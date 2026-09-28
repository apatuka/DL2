// FUN_00459588 @ 00459588 size=210 sig=undefined FUN_00459588() cc=unknown
// callers: FUN_0045cc58
// callees: FUN_004594b8,FUN_0045951c

undefined4 * FUN_00459588(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = (undefined4 *)&DAT_00645370;
  do {
    if (&DAT_00651cb0 <= puVar2) {
      return (undefined4 *)0x0;
    }
    if (*(char *)((int)puVar2 + 6) != '\0') {
      if ((DAT_004d5aa0 == '\0') && (*(char *)(puVar2 + 2) != DAT_0058f1f4)) {
        iVar1 = puVar2[0xe];
      }
      else {
        iVar1 = puVar2[0xf];
      }
      if (((param_1 == iVar1) &&
          (((param_4 != 0 && (*(char *)(puVar2 + 2) != *(char *)(param_1 + 0x20))) ||
           ((param_4 == 0 && (*(char *)(puVar2 + 2) == *(char *)(param_1 + 0x20))))))) &&
         ((*(char *)(puVar2 + 2) == DAT_0058f1f4 ||
          ((((*(byte *)((int)puVar2 + 2) & 1) == 0 || (DAT_00583c20 != 0)) &&
           ('\x01' < *(char *)(param_1 + 0x66 + DAT_0058f1f4))))))) {
        if (*(char *)(param_1 + 0x21) == '\0') {
          iVar1 = FUN_004594b8(puVar2);
        }
        else {
          iVar1 = FUN_0045951c(puVar2);
        }
        if (iVar1 == param_2) {
          if (iVar3 == param_3) {
            return puVar2;
          }
          iVar3 = iVar3 + 1;
        }
      }
    }
    puVar2 = puVar2 + 0x17;
  } while( true );
}

