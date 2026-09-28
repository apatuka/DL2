// FUN_00479050 @ 00479050 size=228 sig=undefined FUN_00479050() cc=unknown
// callers: FUN_00479700,FUN_0047b660,FUN_00479b6c
// callees: 

int FUN_00479050(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char *local_8;
  
  pcVar2 = param_2;
  while (0 < param_3) {
    iVar5 = 1;
    cVar1 = *param_1;
    pcVar3 = param_1;
    while ((pcVar3 = pcVar3 + 1, iVar5 < param_3 && (*pcVar3 == cVar1))) {
      iVar5 = iVar5 + 1;
    }
    if ((1 < iVar5) || (param_3 < 2)) {
      param_3 = param_3 - iVar5;
      param_1 = param_1 + iVar5;
      for (; 0 < iVar5; iVar5 = iVar5 - iVar4) {
        iVar4 = iVar5;
        if (0x80 < iVar5) {
          iVar4 = 0x80;
        }
        *pcVar2 = -((char)iVar4 + -1);
        pcVar2[1] = cVar1;
        pcVar2 = pcVar2 + 2;
      }
    }
    iVar5 = 0;
    local_8 = param_1;
    for (pcVar3 = param_1; (local_8 = local_8 + 1, iVar5 < param_3 && (*pcVar3 != *local_8));
        pcVar3 = pcVar3 + 1) {
      iVar5 = iVar5 + 1;
    }
    param_3 = param_3 - iVar5;
    while (0 < iVar5) {
      iVar4 = iVar5;
      if (0x7f < iVar5) {
        iVar4 = 0x7f;
      }
      iVar5 = iVar5 - iVar4;
      *pcVar2 = (char)iVar4 + -1;
      while( true ) {
        pcVar2 = pcVar2 + 1;
        if (iVar4 == 0) break;
        cVar1 = *param_1;
        param_1 = param_1 + 1;
        *pcVar2 = cVar1;
        iVar4 = iVar4 + -1;
      }
    }
  }
  return (int)pcVar2 - (int)param_2;
}

