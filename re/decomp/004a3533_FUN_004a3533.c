// FUN_004a3533 @ 004a3533 size=1048 sig=undefined FUN_004a3533() cc=unknown
// callers: FUN_004a3d26,FUN_004a3cc8
// callees: FUN_00498ba9,FUN_0049d315,FUN_0049117e,FUN_004989cf,FUN_004a1835,FUN_004a18a9,FUN_0049eb44,FUN_004a33f3,FUN_00495454,FUN_004a3413,FUN_004a191b,FUN_004a3439,FUN_0048e5f8,FUN_004a18c5,FUN_004a1607,FUN_0049e9e8,FUN_004a1715
// strings: \"Unknown opcode in SMenu item list\"

undefined4 FUN_004a3533(int param_1,undefined4 param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint *puVar5;
  undefined4 uVar6;
  int local_8;
  
  iVar3 = FUN_004a3413(param_3);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    while (*param_3 != 0xffffffff) {
      if (*param_3 == 1000) {
        param_3 = (uint *)FUN_004a33f3(param_3);
      }
      else {
        iVar3 = FUN_00498ba9(0x130);
        if (iVar3 == 0) {
          return 0;
        }
        FUN_004a3439(param_1,iVar3);
        *(uint *)(iVar3 + 0x1c) = *param_3;
        param_3 = param_3 + 1;
        while (*param_3 != 0xffffffff) {
          uVar1 = *param_3;
          puVar5 = param_3 + 1;
          switch(uVar1) {
          default:
            FUN_0048e5f8(s_Unknown_opcode_in_SMenu_item_lis_0051e45b);
            param_3 = puVar5;
            break;
          case 1:
            FUN_004a18a9(iVar3 + 0x34);
            uVar4 = FUN_004a18c5(*puVar5,0);
            *(undefined4 *)(iVar3 + 0x34) = uVar4;
            param_3 = param_3 + 2;
            break;
          case 2:
            *(uint *)(iVar3 + 0xc) = *puVar5;
            *(uint *)(iVar3 + 0x10) = param_3[2];
            *(uint *)(iVar3 + 0x18) = param_3[3];
            *(uint *)(iVar3 + 0x14) = param_3[4];
            param_3 = param_3 + 5;
            break;
          case 3:
            *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) | *puVar5;
            param_3 = param_3 + 2;
            break;
          case 4:
            *(uint *)(iVar3 + 0x20) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 5:
            *(uint *)(iVar3 + 0x2c) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 6:
            *(uint *)(iVar3 + 0x30) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 7:
            FUN_004a18a9(iVar3 + 0x34);
            if (*(int *)(param_1 + 0x54) == 0) {
              *(undefined4 *)(iVar3 + 0x34) = 0;
            }
            else {
              uVar6 = 0;
              uVar4 = FUN_0049117e(*(undefined4 *)(param_1 + 0x54),0,*puVar5);
              uVar4 = FUN_004a18c5(uVar4,uVar6);
              *(undefined4 *)(iVar3 + 0x34) = uVar4;
            }
            param_3 = param_3 + 2;
            break;
          case 8:
            *(undefined4 *)(iVar3 + 0x88) = 0;
            param_3 = param_3 + 2;
            break;
          case 9:
            *(undefined4 *)(iVar3 + 0x88) = 0;
            param_3 = param_3 + 2;
            break;
          case 10:
            *(uint *)(iVar3 + 0x24) = *(uint *)(iVar3 + 0x24) | *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0xb:
            param_3 = param_3 + 2;
            FUN_004a1835(param_1,iVar3,*puVar5);
            break;
          case 0xc:
            param_3 = param_3 + 2;
            FUN_004a1607(param_1,iVar3,*puVar5);
            break;
          case 0xd:
            *(uint *)(iVar3 + 0x54) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0xe:
            *(uint *)(iVar3 + 0x58) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0xf:
            param_3 = param_3 + 2;
            FUN_004a191b(iVar3,*puVar5);
            break;
          case 0x11:
            *(uint *)(iVar3 + 0x68) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x12:
            param_3 = param_3 + 2;
            FUN_004a1715(iVar3,*puVar5);
            break;
          case 0x13:
            *(uint *)(iVar3 + 0x48) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x14:
            *(uint *)(iVar3 + 0x44) = *(uint *)(iVar3 + 0x44) | *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x15:
            *(uint *)(iVar3 + 0x9c) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x16:
            *(uint *)(iVar3 + 0xa8) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x17:
            param_3 = (uint *)FUN_0049d315(param_1,iVar3,puVar5);
            break;
          case 0x1b:
            *(uint *)(iVar3 + 0x70) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x1c:
            *(uint *)(iVar3 + 0x6c) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x1d:
            *(uint *)(iVar3 + 0x74) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x1e:
            *(uint *)(iVar3 + 0x78) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x1f:
            *(uint *)(iVar3 + 0xe8) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x20:
            *(uint *)(iVar3 + 0xec) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x21:
            FUN_004a18a9(iVar3 + 0x100);
            if (*(int *)(param_1 + 0x54) == 0) {
              *(undefined4 *)(iVar3 + 0x100) = 0;
            }
            else {
              uVar6 = 0;
              uVar4 = FUN_0049117e(*(undefined4 *)(param_1 + 0x54),0,*puVar5);
              uVar4 = FUN_004a18c5(uVar4,uVar6);
              *(undefined4 *)(iVar3 + 0x100) = uVar4;
            }
            param_3 = param_3 + 2;
            break;
          case 0x22:
          case 0x23:
          case 0x24:
          case 0x25:
            uVar2 = *puVar5;
            param_3 = param_3 + 2;
            puVar5 = (uint *)FUN_00498ba9(uVar2 * 4 + 4);
            if (puVar5 == (uint *)0x0) {
              param_3 = param_3 + uVar2;
            }
            else {
              *puVar5 = uVar2;
              for (local_8 = 0; local_8 < (int)*puVar5; local_8 = local_8 + 1) {
                puVar5[local_8 + 1] = *param_3;
                param_3 = param_3 + 1;
              }
              if (uVar1 == 0x22) {
                local_8 = 0;
              }
              else if (uVar1 == 0x23) {
                local_8 = 1;
              }
              else if (uVar1 == 0x24) {
                local_8 = 2;
              }
              else if (uVar1 == 0x25) {
                local_8 = 3;
              }
              FUN_0049e9e8(iVar3,local_8,puVar5);
              FUN_004989cf(puVar5);
            }
            break;
          case 0x26:
            *(uint *)(iVar3 + 0x108) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x27:
            *(uint *)(iVar3 + 0x10c) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x28:
            *(uint *)(iVar3 + 0x110) = *puVar5;
            param_3 = param_3 + 2;
            break;
          case 0x2a:
            *(uint *)(iVar3 + 0x120) = *puVar5;
            *(uint *)(iVar3 + 0x124) = param_3[2];
            *(uint *)(iVar3 + 0x128) = param_3[3];
            *(uint *)(iVar3 + 300) = param_3[4];
            param_3 = param_3 + 5;
          }
        }
        FUN_00495454(*(undefined4 *)(param_1 + 300),iVar3,param_2);
        if (*(int *)(iVar3 + 0x1c) == 5) {
          if (((DAT_0051e38c & 1) != 0) && ((*(byte *)(iVar3 + 0x24) & 0x80) == 0)) {
            *(uint *)(iVar3 + 0x28) = *(uint *)(iVar3 + 0x28) | 0x80;
          }
          if ((*(byte *)(iVar3 + 0x28) & 0x80) == 0) {
            FUN_0049eb44(param_1,iVar3,2,0x1c,4,0);
          }
        }
        param_3 = param_3 + 1;
        param_2 = *(undefined4 *)(iVar3 + 4);
      }
    }
    uVar4 = 1;
  }
  return uVar4;
}

