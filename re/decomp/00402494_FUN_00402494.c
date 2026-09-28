// FUN_00402494 @ 00402494 size=127 sig=undefined FUN_00402494() cc=unknown
// callers: 
// callees: 

void FUN_00402494(int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = &DAT_004b5104;
  iVar4 = 0;
  do {
    iVar1 = *piVar3 * 0x5a + param_1 * 0x2d8;
    puVar2 = &DAT_0059f1be + iVar1;
    if (param_2 == 0) {
      (**(code **)(&DAT_0059f1c0 + iVar1))(param_1,puVar2);
    }
    else if (param_2 == 1) {
      (**(code **)(&DAT_0059f1c4 + iVar1))(param_1,puVar2);
    }
    else if (param_2 == 2) {
      (**(code **)(&DAT_0059f1c8 + iVar1))(param_1,puVar2);
    }
    else if (param_2 == 3) {
      (**(code **)(&DAT_0059f1cc + iVar1))(param_1,puVar2);
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 6);
  return;
}

