// FUN_004982fc @ 004982fc size=178 sig=undefined FUN_004982fc() cc=unknown
// callers: FUN_004983ae
// callees: 

int FUN_004982fc(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  pcVar2 = param_2;
  for (; 0 < param_3; param_3 = param_3 - iVar3) {
    if ((param_3 < 2) || (*param_1 != param_1[1])) {
      iVar3 = 0;
      for (pcVar5 = param_1;
          ((iVar3 < param_3 && (iVar3 < 0x7f)) &&
          ((param_3 + -2 <= iVar3 || ((*pcVar5 != pcVar5[1] || (*pcVar5 != pcVar5[2]))))));
          pcVar5 = pcVar5 + 1) {
        iVar3 = iVar3 + 1;
      }
      *param_2 = (char)iVar3 + -1;
      iVar4 = iVar3;
      while( true ) {
        param_2 = param_2 + 1;
        iVar4 = iVar4 + -1;
        if (iVar4 < 0) break;
        *param_2 = *param_1;
        param_1 = param_1 + 1;
      }
    }
    else {
      cVar1 = *param_1;
      for (iVar3 = 0;
          ((param_1 = param_1 + 1, iVar3 < param_3 + -1 && (cVar1 == *param_1)) && (iVar3 < 0x7f));
          iVar3 = iVar3 + 1) {
      }
      *param_2 = -(char)iVar3;
      param_2[1] = cVar1;
      param_2 = param_2 + 2;
      iVar3 = iVar3 + 1;
    }
  }
  return (int)param_2 - (int)pcVar2;
}

