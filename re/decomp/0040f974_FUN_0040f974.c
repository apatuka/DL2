// FUN_0040f974 @ 0040f974 size=416 sig=undefined FUN_0040f974() cc=unknown
// callers: FUN_0041026c
// callees: FUN_0040be04,FUN_0040dd80,FUN_0040ded0,FUN_0040f5e0,FUN_0040f794,FUN_004412d4,FUN_0040f700,FUN_0040c68c

void FUN_0040f974(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  int local_10;
  undefined4 *local_c;
  int local_8;
  
  puVar4 = (undefined *)0x0;
  if (param_4 != -1) {
    puVar4 = &DAT_005a43d0 + param_4 * 0xadc;
  }
  iVar1 = FUN_0040f5e0(param_3);
  iVar1 = *(int *)(&DAT_004b6f74 + iVar1 * 4);
  local_8 = -1000000;
  local_c = (undefined4 *)0x0;
  puVar3 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar3) {
      if (local_c != (undefined4 *)0x0) {
        iVar1 = FUN_0040c68c(param_1,2,local_c);
        if (iVar1 == 0) {
          if (*(char *)((int)local_c + 0x21) == '\0') {
            FUN_0040be04(param_1,0xffffffff,0xffffffff,local_c,10,param_2);
          }
          else {
            FUN_0040be04(param_1,0xffffffff,0xffffffff,local_c,2,param_2);
          }
        }
      }
      return;
    }
    if (((*(char *)((int)puVar3 + 0x7e) != '\0') && (*(char *)((int)puVar3 + 0x21) != '\x05')) &&
       (*(char *)((int)puVar3 + 0x21) != '\0')) {
      iVar2 = (int)*(char *)(puVar3 + 8);
      if ((iVar2 != -1) && (param_1 != iVar2)) {
        iVar2 = FUN_004412d4(param_1,iVar2,2);
        if (iVar2 == 0) goto LAB_0040fa9f;
      }
      if ((*(short *)(puVar3 + 0xc) == 0) && (*(short *)(puVar3 + 0x29b) < 3)) {
        iVar2 = FUN_0040f700(puVar3,puVar4,param_3,1);
        if (iVar2 == 0) {
          if ((&DAT_004f9dc3)[iVar1 * 0x32] == '\b') {
            iVar2 = FUN_0040f794(param_1,puVar3,puVar4,param_3);
            if (iVar2 != 0) goto LAB_0040fa4d;
          }
        }
        else {
LAB_0040fa4d:
          local_10 = FUN_0040dd80(puVar3,0,param_1);
          local_10 = local_10 - *(short *)((int)puVar3 + 0xa6e);
          iVar2 = FUN_0040ded0(param_1,puVar3);
          if (iVar2 != 0) {
            local_10 = local_10 + 1000000;
          }
          iVar2 = FUN_0040f700(puVar3,puVar4,param_3,0);
          if (iVar2 != 0) {
            local_10 = local_10 + 100000;
          }
          if (local_8 < local_10) {
            local_8 = local_10;
            local_c = puVar3;
          }
        }
      }
    }
LAB_0040fa9f:
    puVar3 = puVar3 + 0x2b7;
  } while( true );
}

