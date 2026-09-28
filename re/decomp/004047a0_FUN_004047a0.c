// FUN_004047a0 @ 004047a0 size=53 sig=undefined FUN_004047a0() cc=unknown
// callers: 
// callees: 

void FUN_004047a0(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  char *pcStack_8;
  
  bVar5 = (byte)in_stack_0000001c;
  switch(param_2) {
  case 8:
  case 9:
  case 0xd:
  case 0x27:
  case 0x2e:
  case 0x41:
  case 0x4e:
  case 0x96:
    uVar1 = FUN_0046ca40();
    if (((uVar1 & 1) == 0) && (-1 < in_stack_0000001c)) {
      uVar1 = FUN_0046ca40();
      if ((uVar1 & 1) == 0) {
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar2 = FUN_004504a4(param_1,0x1f);
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x1f,uVar2,uVar6,uVar7,uVar8);
      }
      else {
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar2 = FUN_004504a4(param_1,0x22);
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x22,uVar2,uVar6,uVar7,uVar8);
      }
    }
    break;
  case 10:
  case 0xe:
  case 0x25:
  case 0x26:
  case 0x28:
  case 0x2b:
  case 0x2d:
  case 0x51:
  case 0x75:
  case 0x7a:
    if (-1 < in_stack_0000001c) {
      FUN_0040526c(param_1,in_stack_0000001c,0xffffffec);
      if (((1 << (bVar5 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0) &&
         ((*(int *)(&DAT_0052222c + param_1 * 4) == 0 || (uVar1 = FUN_0046ca40(), (uVar1 & 7) == 0))
         )) {
        iVar3 = FUN_00403408(param_1,in_stack_0000001c);
        if (iVar3 == 0) {
          uVar8 = 0;
          uVar7 = 0;
          uVar6 = 0;
          uVar2 = FUN_004504a4(param_1,0x1f);
          FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x1f,uVar2,uVar6,uVar7,uVar8);
        }
        else {
          iVar3 = 0;
          pcStack_8 = &DAT_0059f161;
          do {
            if ((((in_stack_0000001c != iVar3) && (*pcStack_8 != '\0')) && (*pcStack_8 < '\x03')) &&
               ((iVar4 = FUN_00441388(iVar3,in_stack_0000001c,0x10), iVar4 == 0 &&
                ((1 << ((byte)iVar3 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)))) {
              FUN_0045093c(param_1,1 << ((byte)iVar3 & 0x1f),0xffffffff,2,in_stack_0000001c,0,0);
            }
            iVar3 = iVar3 + 1;
            pcStack_8 = pcStack_8 + 0x2d8;
          } while (iVar3 < 7);
        }
      }
      else if (param_2 == 0x25) {
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0xffffffff,5,in_stack_00000020,0,0);
      }
      else if (param_2 == 0x26) {
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0xffffffff,6,in_stack_00000020,0,0);
      }
      else {
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar2 = FUN_004504a4(param_1,0x20);
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x20,uVar2,uVar6,uVar7,uVar8);
      }
    }
    break;
  case 0xb:
  case 0xf:
  case 0x13:
  case 0x14:
  case 0x16:
  case 0x19:
  case 0x24:
  case 0x2c:
  case 0x76:
  case 0x77:
  case 0x95:
    uVar1 = FUN_0046ca40();
    if (((uVar1 & 1) == 0) && (-1 < in_stack_0000001c)) {
      uVar1 = FUN_0046ca40();
      if ((uVar1 & 1) == 0) {
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar2 = FUN_004504a4(param_1,0x1f);
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x1f,uVar2,uVar6,uVar7,uVar8);
      }
      else {
        uVar8 = 0;
        uVar7 = 0;
        uVar6 = 0;
        uVar2 = FUN_004504a4(param_1,0x21);
        FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x21,uVar2,uVar6,uVar7,uVar8);
      }
    }
    break;
  case 0x1f:
  case 0x38:
  case 0x42:
  case 0x4d:
    if ((-1 < in_stack_0000001c) && (uVar1 = FUN_0046ca40(), (uVar1 & 1) == 0)) {
      FUN_0040526c(param_1,in_stack_0000001c,4);
      uVar8 = 0;
      uVar7 = 0;
      uVar6 = 0;
      uVar2 = FUN_004504a4(param_1,0x23);
      FUN_0045093c(param_1,1 << (bVar5 & 0x1f),0x23,uVar2,uVar6,uVar7,uVar8);
    }
    break;
  case 0x3a:
    FUN_00407248(param_1,in_stack_0000001c,in_stack_00000020,1);
    break;
  case 0x72:
    uVar1 = FUN_0046ca40();
    if ((uVar1 & 1) == 0) {
      FUN_00407290(param_1,in_stack_0000001c,in_stack_00000020);
      FUN_00407290(param_1,in_stack_00000020,in_stack_0000001c);
    }
    break;
  case 0x73:
    uVar1 = FUN_0046ca40();
    if ((uVar1 & 1) == 0) {
      FUN_004073a4(param_1,in_stack_0000001c,in_stack_00000020);
      FUN_004073a4(param_1,in_stack_00000020,in_stack_0000001c);
    }
    break;
  case 0x74:
    FUN_004046e8(param_1,in_stack_0000001c,in_stack_00000020);
  }
  return;
}

