// FUN_0045b970 @ 0045b970 size=407 sig=undefined FUN_0045b970() cc=unknown
// callers: FUN_0045be7c,FUN_0045bc10,FUN_0045cd88,FUN_0045bb34,FUN_0045bd44
// callees: FUN_0045973c,FUN_00449cc4

int FUN_0045b970(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int local_58 [4];
  int local_48;
  int local_44;
  int local_40 [4];
  int local_30;
  int local_2c [7];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int local_8;
  
  piVar4 = &DAT_004d1c04;
  piVar3 = local_2c;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar3 = piVar3 + 1;
  }
  piVar4 = &DAT_004d1c20;
  piVar3 = local_40;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar3 = piVar3 + 1;
  }
  FUN_0045973c(DAT_00657de0,local_2c,local_40,&local_8);
  piVar4 = local_2c;
  piVar3 = &DAT_004d1c34;
  piVar5 = local_58;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar5 = piVar5 + 1;
  }
  piVar3 = local_58;
  iVar2 = 0;
  do {
    if (0 < *piVar4) {
      *piVar3 = iVar2;
      piVar3 = piVar3 + 1;
    }
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar2 < 7);
  DAT_004c5450 = 0;
  iVar2 = -1;
  uVar1 = FUN_00449cc4(param_1,param_2,local_c,local_10);
  switch(uVar1) {
  case 0x28:
    if (local_40[0] != 0) {
      iVar2 = 1000;
    }
    break;
  case 0x29:
    if (local_40[1] != 0) {
      if (*(char *)(DAT_00657de0 + 0x21) == '\0') {
        if (local_8 != 0) {
          iVar2 = 0x3ed;
        }
      }
      else {
        iVar2 = 0x3e9;
      }
    }
    break;
  case 0x2a:
    if (local_40[2] != 0) {
      iVar2 = 0x3ea;
    }
    break;
  case 0x2b:
    if (local_40[3] != 0) {
      iVar2 = 0x3eb;
    }
    break;
  case 0x2c:
    if (local_30 != 0) {
      iVar2 = 0x3ec;
    }
    break;
  case 0x2d:
    if (local_58[0] != -1) {
      iVar2 = local_58[0] + 9000;
    }
    break;
  case 0x2e:
    if (local_58[1] != -1) {
      iVar2 = local_58[1] + 9000;
    }
    break;
  case 0x2f:
    if (local_58[2] != -1) {
      iVar2 = local_58[2] + 9000;
    }
    break;
  case 0x30:
    if (local_58[3] != -1) {
      iVar2 = local_58[3] + 9000;
    }
    break;
  case 0x31:
    if (local_48 != -1) {
      iVar2 = local_48 + 9000;
    }
    break;
  case 0x32:
    if (local_44 != -1) {
      iVar2 = local_44 + 9000;
    }
  }
  DAT_004c5450 = 1;
  return iVar2;
}

