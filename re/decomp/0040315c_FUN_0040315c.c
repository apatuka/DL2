// FUN_0040315c @ 0040315c size=84 sig=undefined FUN_0040315c() cc=unknown
// callers: 
// callees: memset

void FUN_0040315c(int param_1,int param_2)

{
  int *piVar1;
  undefined2 *puVar2;
  
  memset(param_2,0,0x54);
  for (puVar2 = &DAT_005f0410; puVar2 < &DAT_00645370; puVar2 = puVar2 + 0x91) {
    if ((puVar2 != (undefined2 *)0x0) &&
       (param_1 == (char)(&DAT_005a43f0)[(short)puVar2[4] * 0xadc])) {
      piVar1 = (int *)(param_2 + *(char *)((int)puVar2 + 5) * 4);
      *piVar1 = *piVar1 + 1;
    }
  }
  return;
}

