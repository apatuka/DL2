// FUN_00403ba0 @ 00403ba0 size=99 sig=undefined FUN_00403ba0() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00403ba0(int param_1)

{
  undefined2 *puVar1;
  
  puVar1 = &DAT_005f0410;
  while( true ) {
    if ((undefined2 *)0x64536f < puVar1) {
      return 0;
    }
    if ((((*(char *)(puVar1 + 2) == '\x18') && (puVar1[10] != 0)) &&
        (*(char *)(puVar1 + 7) == '\x02')) &&
       (param_1 == (char)(&DAT_005a43f0)[(short)puVar1[4] * 0xadc])) break;
    puVar1 = puVar1 + 0x91;
  }
  return 1;
}

