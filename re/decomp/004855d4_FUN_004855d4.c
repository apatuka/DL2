// FUN_004855d4 @ 004855d4 size=145 sig=undefined FUN_004855d4() cc=unknown
// callers: FUN_00485668
// callees: 

ushort * FUN_004855d4(int param_1)

{
  char cVar1;
  ushort *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  ushort *local_8;
  
  local_8 = (ushort *)0x0;
  uVar6 = 0x7fffffff;
  iVar5 = 0;
  while ((iVar5 < 2 && (local_8 == (ushort *)0x0))) {
    iVar3 = 0;
    puVar4 = (undefined4 *)(param_1 + 0x154);
    do {
      puVar2 = (ushort *)*puVar4;
      if (puVar2 != (ushort *)0x0) {
        cVar1 = *(char *)((int)puVar2 + 5);
        if (((byte)(cVar1 - 2U) < 3) || (cVar1 == '\n')) {
          if ((*puVar2 < uVar6) && ((puVar2[10] == 0 && (iVar5 == 1)))) {
            uVar6 = (uint)*puVar2;
            local_8 = puVar2;
          }
        }
        else if ((((cVar1 == '\x12') && (*puVar2 < uVar6)) && (puVar2[10] == 0)) && (iVar5 == 0)) {
          uVar6 = (uint)*puVar2;
          local_8 = puVar2;
        }
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0xd;
    } while (iVar3 < 0x24);
    iVar5 = iVar5 + 1;
  }
  return local_8;
}

