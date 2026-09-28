// FUN_004a19b4 @ 004a19b4 size=533 sig=undefined FUN_004a19b4() cc=unknown
// callers: FUN_0043aa88,FUN_0042e4f0,FUN_00427fe0,FUN_004281f4,FUN_0043a394,FUN_004256f4,FUN_0042e584,FUN_0043735c
// callees: FUN_0049eb44,FUN_0049ea99,FUN_004a1150,FUN_004a191b,FUN_004a196e,FUN_004a1835,FUN_004a18c5,FUN_004a118a,FUN_004a18a9,FUN_004a1715

undefined4
FUN_004a19b4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            int *param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  uVar4 = 1;
  iVar1 = FUN_004a1150(param_1,param_2,param_3);
  if (iVar1 == 0) {
    uVar4 = 0;
  }
  else {
    switch(param_4) {
    default:
      uVar4 = 0;
      break;
    case 1:
      FUN_004a18a9(iVar1 + 0x34);
      uVar2 = FUN_004a18c5(param_5,0);
      *(undefined4 *)(iVar1 + 0x34) = uVar2;
      FUN_0049eb44(param_1,iVar1,2,0x1c,3,0);
      break;
    case 2:
      if (param_5 != (int *)0x0) {
        FUN_004a118a(iVar1,*param_5,param_5[1],1);
        *(int *)(iVar1 + 0x14) = param_5[3] - param_5[1];
        *(int *)(iVar1 + 0x18) = param_5[2] - *param_5;
      }
      break;
    case 3:
      *(int **)(iVar1 + 0x28) = param_5;
      break;
    case 4:
      *(int **)(iVar1 + 0x20) = param_5;
      break;
    case 5:
      *(int **)(iVar1 + 0x2c) = param_5;
      break;
    case 6:
      *(int **)(iVar1 + 0x30) = param_5;
      break;
    case 10:
      *(int **)(iVar1 + 0x24) = param_5;
      break;
    case 0xb:
      FUN_004a1835(param_1,iVar1,param_5);
      break;
    case 0xc:
      FUN_004a196e(param_1,iVar1,param_5);
      break;
    case 0xd:
      uVar9 = 0;
      uVar8 = 0;
      uVar7 = 8;
      uVar6 = 2;
      iVar3 = iVar1;
      uVar2 = FUN_0049ea99(iVar1);
      FUN_0049eb44(uVar2,iVar3,uVar6,uVar7,uVar8,uVar9);
      *(int **)(iVar1 + 0x54) = param_5;
      uVar9 = 0;
      uVar8 = 0;
      uVar7 = 8;
      uVar6 = 2;
      uVar2 = FUN_0049ea99(iVar1);
      FUN_0049eb44(uVar2,iVar1,uVar6,uVar7,uVar8,uVar9);
      break;
    case 0xe:
      *(int **)(iVar1 + 0x58) = param_5;
      break;
    case 0xf:
      FUN_004a191b(iVar1,param_5);
      break;
    case 0x10:
      *(int **)(iVar1 + 0x40) = param_5;
      break;
    case 0x11:
      *(int **)(iVar1 + 0x68) = param_5;
      break;
    case 0x12:
      FUN_004a1715(iVar1,param_5);
      break;
    case 0x13:
      uVar9 = 0;
      uVar8 = 0;
      uVar7 = 8;
      uVar6 = 2;
      iVar3 = iVar1;
      uVar2 = FUN_0049ea99(iVar1);
      FUN_0049eb44(uVar2,iVar3,uVar6,uVar7,uVar8,uVar9);
      *(int **)(iVar1 + 0x48) = param_5;
      break;
    case 0x14:
      *(int **)(iVar1 + 0x44) = param_5;
      break;
    case 0x15:
      *(int **)(iVar1 + 0x9c) = param_5;
      break;
    case 0x16:
      *(int **)(iVar1 + 0xa8) = param_5;
      break;
    case 0x1b:
      *(int **)(iVar1 + 0x70) = param_5;
      break;
    case 0x1c:
      *(int **)(iVar1 + 0x6c) = param_5;
      break;
    case 0x1d:
      *(int **)(iVar1 + 0x74) = param_5;
      break;
    case 0x1e:
      *(int **)(iVar1 + 0x78) = param_5;
      break;
    case 0x1f:
      uVar9 = 0;
      uVar8 = 0;
      uVar7 = 8;
      uVar6 = 2;
      iVar3 = iVar1;
      uVar2 = FUN_0049ea99(iVar1);
      FUN_0049eb44(uVar2,iVar3,uVar6,uVar7,uVar8,uVar9);
      *(int **)(iVar1 + 0xe8) = param_5;
      break;
    case 0x20:
      uVar9 = 0;
      uVar8 = 0;
      uVar7 = 8;
      uVar6 = 2;
      iVar3 = iVar1;
      uVar2 = FUN_0049ea99(iVar1);
      FUN_0049eb44(uVar2,iVar3,uVar6,uVar7,uVar8,uVar9);
      *(int **)(iVar1 + 0xec) = param_5;
      break;
    case 0x21:
      FUN_004a18a9(iVar1 + 0x100);
      uVar2 = FUN_004a18c5(param_5,0);
      *(undefined4 *)(iVar1 + 0x100) = uVar2;
      break;
    case 0x26:
      *(int **)(iVar1 + 0x108) = param_5;
      break;
    case 0x27:
      *(int **)(iVar1 + 0x10c) = param_5;
      break;
    case 0x28:
      *(int **)(iVar1 + 0x110) = param_5;
      break;
    case 0x2a:
      if (param_5 != (int *)0x0) {
        piVar5 = (int *)(iVar1 + 0x120);
        for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar5 = *param_5;
          param_5 = param_5 + 1;
          piVar5 = piVar5 + 1;
        }
        uVar4 = 1;
      }
    }
  }
  return uVar4;
}

