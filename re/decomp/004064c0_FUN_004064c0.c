// FUN_004064c0 @ 004064c0 size=119 sig=undefined FUN_004064c0() cc=unknown
// callers: 
// callees: 

int FUN_004064c0(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int local_c;
  
  piVar2 = param_2;
  local_c = 0;
  do {
    iVar7 = 0;
    piVar6 = (int *)(*param_2 + 0x154);
    do {
      iVar1 = *piVar6;
      if ((iVar1 != 0) && (*(char *)(iVar1 + 5) == '\x11')) {
        iVar5 = 0;
        piVar4 = (int *)(iVar1 + 0x18);
        pcVar3 = (char *)(iVar1 + 0x2c);
        do {
          if (*pcVar3 == '\x14') {
            local_c = local_c + *piVar4;
          }
          iVar5 = iVar5 + 1;
          piVar4 = piVar4 + 1;
          pcVar3 = pcVar3 + 1;
        } while (iVar5 < 5);
      }
      iVar7 = iVar7 + 1;
      piVar6 = piVar6 + 0xd;
    } while (iVar7 < 0x24);
    param_2 = (int *)param_2[1];
  } while (param_2 != piVar2);
  return local_c;
}

