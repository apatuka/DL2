// FUN_0040df44 @ 0040df44 size=266 sig=undefined FUN_0040df44() cc=unknown
// callers: FUN_0040a524
// callees: FUN_0040dd80,FUN_0040ded0,FUN_004412d4

undefined4 * FUN_0040df44(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int local_10;
  undefined4 *local_c;
  int local_8;
  
  puVar2 = &DAT_005a4eac;
  local_8 = -1000000;
  local_c = (undefined4 *)0x0;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar2) {
      return local_c;
    }
    if ((((*(char *)((int)puVar2 + 0x7e) != '\0') && (*(char *)((int)puVar2 + 0x21) != '\x05')) &&
        ((param_3 == 0 || ((*(char *)((int)puVar2 + 0x21) == '\0' && (puVar2[0x22b] != 0)))))) &&
       ((param_3 != 0 || (*(char *)((int)puVar2 + 0x21) != '\0')))) {
      iVar1 = (int)*(char *)(puVar2 + 8);
      if ((iVar1 != -1) && (param_1 != iVar1)) {
        iVar1 = FUN_004412d4(param_1,iVar1,2);
        if (iVar1 == 0) goto LAB_0040e021;
      }
      if ((*(short *)(puVar2 + 0xc) == 0) && (*(short *)(puVar2 + 0x29b) < 3)) {
        local_10 = FUN_0040dd80(puVar2,param_2,param_1);
        local_10 = local_10 - *(short *)((int)puVar2 + 0xa6e);
        iVar1 = FUN_0040ded0(param_1,puVar2);
        if (iVar1 != 0) {
          local_10 = local_10 + 1000000;
        }
        if (*(short *)(puVar2 + 0x29b) < 2) {
          local_10 = local_10 + 100000;
        }
        if (local_8 < local_10) {
          local_8 = local_10;
          local_c = puVar2;
        }
      }
    }
LAB_0040e021:
    puVar2 = puVar2 + 0x2b7;
  } while( true );
}

