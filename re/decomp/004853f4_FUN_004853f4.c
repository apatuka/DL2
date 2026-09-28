// FUN_004853f4 @ 004853f4 size=133 sig=undefined FUN_004853f4() cc=unknown
// callers: FUN_00485668
// callees: FUN_00446b3c

int FUN_004853f4(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = -1;
  sVar2 = 1000;
  FUN_00446b3c(param_2,100,3,param_1,0x2000 << ((byte)param_1 & 0x1f));
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    if ((((0x2000 << ((byte)param_1 & 0x1f) & puVar1[7]) != 0) && (param_1 == *(char *)(puVar1 + 8))
        ) && (*(short *)((int)puVar1 + param_1 * 2 + 0xa70) < sVar2)) {
      sVar2 = *(short *)((int)puVar1 + param_1 * 2 + 0xa70);
      iVar3 = (int)*(short *)((int)puVar1 + 0x1a);
    }
  }
  return iVar3;
}

