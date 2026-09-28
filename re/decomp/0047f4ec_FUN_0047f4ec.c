// FUN_0047f4ec @ 0047f4ec size=215 sig=undefined FUN_0047f4ec() cc=unknown
// callers: FUN_00480150,FUN_0047ff5c
// callees: FUN_0047f440

undefined * FUN_0047f4ec(int param_1)

{
  int iVar1;
  undefined *puVar2;
  
  if ((DAT_004dccbc == 0) || (*(char *)(param_1 + 5) == '\x14')) {
    if (*(short *)(param_1 + 0x14) == 0) {
      puVar2 = (&PTR_DAT_004d02f4)
               [((int)(short)(&DAT_004f9dc0)[*(char *)(param_1 + 4) * 0x19] +
                (int)*(char *)(param_1 + 6)) * 3];
      if (DAT_004dccbc == 0) {
        if ((*(byte *)(param_1 + 2) & 4) != 0) {
          puVar2 = puVar2 + 0x10;
        }
        if ((*(int *)(puVar2 + 8) == 0) ||
           ((*(short *)(puVar2 + 4) == 0 && (*(short *)(puVar2 + 6) == 0)))) {
          puVar2 = puVar2 + -0x10;
        }
      }
    }
    else {
      iVar1 = FUN_0047f440(param_1);
      puVar2 = (&PTR_DAT_004d02f4)[iVar1 * 3];
      if (((*(ushort *)(param_1 + 2) & 4) != 0) && ((*(ushort *)(param_1 + 2) & 2) != 0)) {
        puVar2 = puVar2 + 0x10;
      }
      if ((*(int *)(puVar2 + 8) == 0) ||
         ((*(short *)(puVar2 + 4) == 0 && (*(short *)(puVar2 + 6) == 0)))) {
        puVar2 = puVar2 + -0x10;
      }
    }
  }
  else if ((&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32] == '\x02') {
    puVar2 = &DAT_004ed08c;
  }
  else {
    puVar2 = &DAT_004ed07c;
  }
  return puVar2;
}

