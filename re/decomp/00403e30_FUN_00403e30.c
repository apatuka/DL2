// FUN_00403e30 @ 00403e30 size=226 sig=undefined FUN_00403e30() cc=unknown
// callers: 
// callees: FUN_00476448,FUN_00475a60,FUN_0044d1a4,FUN_00401ac0,FUN_00403dbc,FUN_0046b0e4,FUN_00475854

void FUN_00403e30(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined2 *puVar3;
  int *piVar4;
  int iVar5;
  int local_c;
  int local_8;
  
  puVar3 = &DAT_00645370;
  do {
    if ((undefined2 *)0x651caf < puVar3) {
      piVar4 = &DAT_00521bb4;
      do {
        iVar5 = *piVar4;
        iVar1 = FUN_0044d1a4(iVar5,0x11,0);
        if (iVar1 != -1) {
          local_8 = (int)*(short *)(param_2 + 0x30);
          local_c = FUN_0046b0e4(iVar5);
          local_c = local_c - *(short *)(iVar5 + 0x30);
          if (local_c < local_8) {
            piVar2 = &local_c;
          }
          else {
            piVar2 = &local_8;
          }
          if (0 < *piVar2) {
            FUN_00476448(param_2,iVar5,*piVar2,0,0xffffffff,0xffffffff);
          }
        }
        piVar4 = (int *)piVar4[1];
      } while (piVar4 != &DAT_00521bb4);
      iVar5 = 0;
      piVar4 = (int *)(param_2 + 0x154);
      do {
        if ((*piVar4 != 0) && (*(char *)(*piVar4 + 5) == '\x11')) {
          FUN_00475a60(param_2,iVar5,0);
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 0xd;
      } while (iVar5 < 0x24);
      return;
    }
    if (((*(char *)(puVar3 + 3) != '\0') && (param_1 == *(char *)(puVar3 + 4))) &&
       (param_2 == *(int *)(puVar3 + 0x1e))) {
      iVar5 = FUN_00403dbc(param_2,puVar3);
      if (iVar5 != 0) {
        iVar5 = FUN_00401ac0(puVar3,iVar5,0);
        if (iVar5 != 0) goto LAB_00403e7a;
      }
      FUN_00475854(puVar3);
    }
LAB_00403e7a:
    puVar3 = puVar3 + 0x2e;
  } while( true );
}

