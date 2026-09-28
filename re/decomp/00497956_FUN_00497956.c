// FUN_00497956 @ 00497956 size=130 sig=undefined FUN_00497956() cc=unknown
// callers: 
// callees: FUN_0049721c,FUN_004974ef,FUN_004a6b00,FUN_004976dc,FUN_00497859,FUN_0049716d

undefined4
FUN_00497956(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_104 [256];
  
  pcVar1 = (char *)FUN_004976dc(param_1,param_2);
  if (pcVar1 == (char *)0x0) {
    uVar3 = 0;
  }
  else {
    do {
      pcVar1 = (char *)FUN_0049716d(pcVar1);
      if ((pcVar1 == (char *)0x0) || (*pcVar1 == '[')) {
        return 0;
      }
      FUN_004974ef(pcVar1,local_104);
      iVar2 = FUN_004a6b00(local_104,param_3);
    } while (iVar2 != 0);
    iVar2 = FUN_0049721c(pcVar1);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00497859(iVar2);
      *param_4 = uVar3;
      uVar3 = 1;
    }
  }
  return uVar3;
}

