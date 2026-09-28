// FUN_0043d2d8 @ 0043d2d8 size=554 sig=undefined FUN_0043d2d8() cc=unknown
// callers: FUN_00455c88
// callees: FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_00486564,FUN_00444b74

void FUN_0043d2d8(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  uint uVar9;
  undefined4 uVar10;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x38) != 0)) && (*(char *)(param_1 + 0x1d) != '\0')) {
    uVar10 = 0;
    uVar2 = FUN_0043d004((int)*(short *)(*(int *)(param_1 + 0x38) + 0xe));
    FUN_00482ac4(*(undefined4 *)(&DAT_004faf94 + *(int *)(param_1 + 4) * 0x24),0,1,0,uVar2,uVar10);
    sVar8 = 1;
    sVar7 = 1;
    switch(*(undefined4 *)(param_1 + 4)) {
    case 4:
      sVar8 = 2;
    case 3:
      sVar8 = sVar8 + 1;
    case 2:
      sVar7 = sVar8 + 1;
    default:
      iVar6 = *(int *)(param_1 + 0x38);
      if (*(short *)(iVar6 + 0x2c) == 2) {
        return;
      }
      *(undefined2 *)(iVar6 + 0x2c) = 1;
      *(short *)(iVar6 + 0x2e) = sVar7 + -1;
      iVar6 = *(int *)(param_1 + 0x3c);
      if (iVar6 == 0) {
        return;
      }
      iVar3 = *(int *)(iVar6 + 0x20) - *(int *)(param_1 + 0x20);
      iVar5 = *(int *)(iVar6 + 0x24) - *(int *)(param_1 + 0x24);
      uVar9 = 0;
      if (iVar3 < 1) {
        if (iVar3 < 0) {
          uVar9 = 8;
        }
      }
      else {
        uVar9 = 2;
      }
      if (iVar5 < 0) {
        uVar9 = uVar9 | 1;
      }
      else if (*(int *)(iVar6 + 0x24) != *(int *)(param_1 + 0x24) && -1 < iVar5) {
        uVar9 = uVar9 | 4;
      }
      if (uVar9 == 0) {
        return;
      }
      uVar1 = FUN_00486564(uVar9);
      *(undefined2 *)(*(int *)(param_1 + 0x38) + 0x30) = uVar1;
      return;
    case 5:
      uVar2 = 0x198;
      sVar8 = 1;
      break;
    case 6:
      uVar2 = 0x199;
      sVar8 = 2;
      break;
    case 7:
      uVar2 = 0x19a;
      sVar8 = 3;
      break;
    case 8:
      uVar2 = 0x19b;
      sVar8 = 4;
      break;
    case 9:
      uVar2 = 0x19c;
      sVar8 = 1;
      break;
    case 10:
      uVar2 = 0x19d;
      sVar8 = 2;
      break;
    case 0xb:
      uVar2 = 0x19e;
      sVar8 = 3;
      break;
    case 0xc:
      uVar2 = 0x19f;
      sVar8 = 1;
      break;
    case 0xd:
      uVar2 = 0x1a0;
      sVar8 = 1;
      break;
    case 0xe:
      uVar2 = 0x1a1;
      sVar8 = 1;
      break;
    case 0x19:
      uVar2 = 0x1aa;
      sVar8 = 1;
      break;
    case 0x1b:
      uVar2 = 0x1a2;
      sVar8 = 2;
      break;
    case 0x1c:
      uVar2 = 0x1a3;
      sVar8 = 1;
      break;
    case 0x1d:
      uVar2 = 0x1a4;
      sVar8 = 1;
      break;
    case 0x1e:
      uVar2 = 0x1a5;
      sVar8 = 1;
      break;
    case 0x1f:
      uVar2 = 0x1a9;
      sVar8 = 1;
      break;
    case 0x21:
      uVar2 = 0x1a6;
      sVar8 = 1;
      break;
    case 0x22:
      uVar2 = 0x1a7;
      sVar8 = 1;
      break;
    case 0x23:
      uVar2 = 0x1a8;
      sVar8 = 1;
    }
    puVar4 = (ushort *)FUN_00444f20(uVar2,0,0,0);
    if (puVar4 != (ushort *)0x0) {
      puVar4[0x17] = sVar8 - 1;
      puVar4[0x18] = *(ushort *)(*(int *)(param_1 + 0x38) + 0x30);
      iVar6 = *(int *)(param_1 + 0x38) + -0x561a34;
      if (iVar6 < 0) {
        iVar6 = *(int *)(param_1 + 0x38) + -0x5619f5;
      }
      puVar4[0x19] = (ushort)(iVar6 >> 6);
      *puVar4 = *puVar4 | 0x10;
      FUN_00444b74(puVar4,*(short *)(*(int *)(param_1 + 0x38) + 4) + 1);
    }
  }
  return;
}

