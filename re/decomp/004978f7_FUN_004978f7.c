// FUN_004978f7 @ 004978f7 size=95 sig=undefined FUN_004978f7() cc=unknown
// callers: 
// callees: FUN_0049721c,FUN_004976dc,FUN_00497859,FUN_0049716d

char * FUN_004978f7(undefined4 param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = (char *)FUN_004976dc(param_1,param_2);
  if (pcVar2 != (char *)0x0) {
    bVar1 = false;
    while (!bVar1) {
      pcVar2 = (char *)FUN_0049716d(pcVar2);
      if ((pcVar2 == (char *)0x0) || (*pcVar2 == '[')) {
        bVar1 = true;
        pcVar2 = (char *)0x0;
      }
      else {
        iVar3 = FUN_0049721c(pcVar2);
        if (iVar3 != 0) {
          iVar3 = FUN_00497859(iVar3);
          if (iVar3 == param_3) {
            bVar1 = true;
          }
        }
      }
    }
  }
  return pcVar2;
}

