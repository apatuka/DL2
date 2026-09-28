// FUN_004a1c75 @ 004a1c75 size=403 sig=undefined FUN_004a1c75() cc=unknown
// callers: FUN_0042df28,FUN_004272b4
// callees: FUN_004a1150,FUN_004a6964

undefined4
FUN_004a1c75(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  uVar4 = 1;
  if ((param_5 == (undefined4 *)0x0) || (iVar1 = FUN_004a1150(param_1,param_2,param_3), iVar1 == 0))
  {
    uVar4 = 0;
  }
  else {
    switch(param_4) {
    default:
      uVar4 = 0;
      break;
    case 1:
      if (*(int *)(iVar1 + 0x34) == 0) {
        *(undefined1 *)param_5 = 0;
      }
      else {
        FUN_004a6964(param_5,*(undefined4 *)(iVar1 + 0x34));
      }
      break;
    case 2:
      param_5[1] = *(undefined4 *)(iVar1 + 0x10);
      *param_5 = *(undefined4 *)(iVar1 + 0xc);
      param_5[3] = *(int *)(iVar1 + 0x10) + *(int *)(iVar1 + 0x14);
      param_5[2] = *(int *)(iVar1 + 0xc) + *(int *)(iVar1 + 0x18);
      break;
    case 3:
      *param_5 = *(undefined4 *)(iVar1 + 0x28);
      break;
    case 4:
      *param_5 = *(undefined4 *)(iVar1 + 0x20);
      break;
    case 5:
      *param_5 = *(undefined4 *)(iVar1 + 0x2c);
      break;
    case 6:
      *param_5 = *(undefined4 *)(iVar1 + 0x30);
      break;
    case 10:
      *param_5 = *(undefined4 *)(iVar1 + 0x24);
      break;
    case 0xb:
      *param_5 = *(undefined4 *)(iVar1 + 0xe4);
      break;
    case 0xc:
      *param_5 = *(undefined4 *)(iVar1 + 0x38);
      break;
    case 0xd:
      *param_5 = *(undefined4 *)(iVar1 + 0x54);
      break;
    case 0xe:
      *param_5 = *(undefined4 *)(iVar1 + 0x58);
      break;
    case 0xf:
      *param_5 = *(undefined4 *)(iVar1 + 0x60);
      break;
    case 0x10:
      *param_5 = *(undefined4 *)(iVar1 + 0x40);
      break;
    case 0x11:
      *param_5 = *(undefined4 *)(iVar1 + 0x68);
      break;
    case 0x12:
      *param_5 = *(undefined4 *)(iVar1 + 0x3c);
      break;
    case 0x13:
      *param_5 = *(undefined4 *)(iVar1 + 0x48);
      break;
    case 0x14:
      *param_5 = *(undefined4 *)(iVar1 + 0x44);
      break;
    case 0x15:
      *param_5 = *(undefined4 *)(iVar1 + 0x9c);
      break;
    case 0x16:
      *param_5 = *(undefined4 *)(iVar1 + 0xa8);
      break;
    case 0x1b:
      *param_5 = *(undefined4 *)(iVar1 + 0x70);
      break;
    case 0x1c:
      *param_5 = *(undefined4 *)(iVar1 + 0x6c);
      break;
    case 0x1d:
      *param_5 = *(undefined4 *)(iVar1 + 0x74);
      break;
    case 0x1e:
      *param_5 = *(undefined4 *)(iVar1 + 0x78);
      break;
    case 0x1f:
      *param_5 = *(undefined4 *)(iVar1 + 0xe8);
      break;
    case 0x20:
      *param_5 = *(undefined4 *)(iVar1 + 0xec);
      break;
    case 0x26:
      *param_5 = *(undefined4 *)(iVar1 + 0x108);
      break;
    case 0x27:
      *param_5 = *(undefined4 *)(iVar1 + 0x10c);
      break;
    case 0x28:
      *param_5 = *(undefined4 *)(iVar1 + 0x110);
      break;
    case 0x2a:
      puVar3 = (undefined4 *)(iVar1 + 0x120);
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_5 = *puVar3;
        puVar3 = puVar3 + 1;
        param_5 = param_5 + 1;
      }
      uVar4 = 1;
    }
  }
  return uVar4;
}

