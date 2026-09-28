// FUN_0049cd32 @ 0049cd32 size=495 sig=undefined FUN_0049cd32() cc=unknown
// callers: FUN_004a2498
// callees: FUN_0049ccb0,FUN_0049eb44,FUN_004addb4

undefined4 FUN_0049cd32(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char local_110 [256];
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = FUN_0049eb44(param_1,param_2,2,0x18,0,0);
  local_c = FUN_0049eb44(param_1,param_2,2,0x22,0,0);
  iVar3 = local_c + 1;
  local_10 = 2;
  do {
    if (iVar3 < local_8) {
      do {
        iVar1 = FUN_0049eb44(param_1,param_2,2,0x35,iVar3,0);
        if ((iVar1 < 0x100) && (iVar1 != 0)) {
          FUN_0049eb44(param_1,param_2,2,0x35,iVar3,local_110);
          iVar1 = FUN_004addb4((int)local_110[0]);
          iVar2 = FUN_004addb4(param_3);
          if (iVar1 == iVar2) {
            FUN_0049eb44(param_1,param_2,2,0x1b,iVar3,0);
            FUN_0049eb44(param_1,param_2,2,0x21,iVar3,0);
            local_10 = 0;
            break;
          }
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < local_8);
    }
    local_10 = local_10 + -1;
    iVar3 = 0;
    if (local_10 < 1) {
      switch(param_3) {
      case 0x101:
        FUN_0049eb44(param_1,param_2,2,0x21,0xffffffff,3);
        FUN_0049eb44(param_1,param_2,2,0x1b,*(undefined4 *)(param_2 + 0x98),0);
        break;
      default:
        return 0;
      case 0x103:
        FUN_0049eb44(param_1,param_2,2,0x21,1,3);
        iVar3 = FUN_0049ccb0(param_1,param_2);
        local_c = iVar3 + *(int *)(param_2 + 0x98) + -1;
        if (local_8 <= local_c) {
          local_c = local_8 + -1;
        }
        if (local_c < 0) {
          local_c = 0;
        }
        FUN_0049eb44(param_1,param_2,2,0x1b,local_c,0);
        break;
      case 0x104:
        if (local_c < local_8 + -1) {
          FUN_0049eb44(param_1,param_2,2,0x1b,local_c + 1,0);
          FUN_0049eb44(param_1,param_2,2,0x21,local_c + 1,0);
        }
        break;
      case 0x105:
        FUN_0049eb44(param_1,param_2,2,0x21,0x7fff,0);
        break;
      case 0x107:
        FUN_0049eb44(param_1,param_2,2,0x21,0,0);
        break;
      case 0x108:
        if (0 < local_c) {
          FUN_0049eb44(param_1,param_2,2,0x1b,local_c + -1,0);
          FUN_0049eb44(param_1,param_2,2,0x21,local_c + -1,0);
        }
      }
      return 1;
    }
  } while( true );
}

