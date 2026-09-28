// FUN_00448314 @ 00448314 size=182 sig=undefined FUN_00448314() cc=unknown
// callers: FUN_00401670,FUN_00451508
// callees: 

int FUN_00448314(int param_1,int param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x75) * 4);
  iVar4 = (int)*pcVar1;
  iVar3 = (int)pcVar1[1];
  pcVar1 = *(char **)(param_2 + 0x80 + *(char *)(param_2 + 0x75) * 4);
  iVar5 = (int)*pcVar1;
  iVar2 = (int)pcVar1[1];
  if (iVar5 < iVar4) {
    iVar6 = iVar4 - iVar5;
  }
  else {
    iVar6 = iVar5 - iVar4;
  }
  if (iVar2 < iVar3) {
    iVar7 = iVar3 - iVar2;
  }
  else {
    iVar7 = iVar2 - iVar3;
  }
  if (iVar7 < iVar6) {
    if (iVar5 < iVar4) {
      iVar2 = 2;
    }
    else {
      iVar2 = 8;
    }
  }
  else if (iVar2 < iVar3) {
    iVar2 = 4;
  }
  else {
    iVar2 = 1;
  }
  if ((*(char *)(param_2 + 0x21) == '\x04') && (param_3 == 0)) {
    if (iVar2 == 8) {
      iVar2 = 4;
    }
    if (iVar2 == 1) {
      iVar2 = 2;
    }
  }
  return iVar2;
}

