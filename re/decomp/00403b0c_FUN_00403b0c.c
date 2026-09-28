// FUN_00403b0c @ 00403b0c size=148 sig=undefined FUN_00403b0c() cc=unknown
// callers: 
// callees: 

int FUN_00403b0c(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  piVar6 = param_2;
  if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) != 0) {
    do {
      iVar1 = *piVar6;
      if (*(char *)(iVar1 + 0x27) < 'd') {
        bVar3 = false;
        iVar4 = 0;
        piVar5 = (int *)(iVar1 + 0x154);
        do {
          iVar2 = *piVar5;
          if (((iVar2 != 0) && (*(short *)(iVar2 + 0x14) == 0)) && (*(char *)(iVar2 + 5) == '\x06'))
          {
            bVar3 = true;
            break;
          }
          iVar4 = iVar4 + 1;
          piVar5 = piVar5 + 0xd;
        } while (iVar4 < 0x24);
        if (!bVar3) {
          return iVar1;
        }
      }
      piVar6 = (int *)piVar6[1];
    } while (piVar6 != param_2);
  }
  return 0;
}

