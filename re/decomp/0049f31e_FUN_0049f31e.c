// FUN_0049f31e @ 0049f31e size=420 sig=undefined FUN_0049f31e() cc=unknown
// callers: FUN_0049f4c2,FUN_004a2cb5
// callees: FUN_0049eb44,FUN_00495c51,FUN_0049f09b,FUN_00495d89

int FUN_0049f31e(undefined4 param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int local_44 [4];
  undefined4 local_34;
  undefined4 local_30;
  int local_24 [4];
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  if (param_2 != 0) {
    if (*(int *)(param_2 + 0x1c) == 4) {
      if ((*(byte *)(param_2 + 0x28) & 0x10) != 0) {
        FUN_0049f09b(param_2,&local_34);
        for (iVar2 = 0; iVar2 < *(int *)(param_2 + 0x8c); iVar2 = iVar2 + 1) {
          FUN_0049eb44(param_1,param_2,2,0x1d,iVar2,local_24);
          FUN_00495c51(local_24,local_34,local_30);
          if ((((local_24[0] <= param_3) && (param_3 < local_24[2])) && (local_24[1] <= param_4)) &&
             (param_4 < local_24[3])) {
            if (param_5 != (int *)0x0) {
              *param_5 = param_3 - local_24[0];
            }
            if (param_6 == (int *)0x0) {
              return iVar2;
            }
            *param_6 = param_4 - local_24[1];
            return iVar2;
          }
        }
      }
    }
    else if (*(int *)(param_2 + 0x1c) == 6) {
      local_8 = FUN_0049eb44(param_1,param_2,2,0x17,0,0);
      local_c = FUN_0049eb44(param_1,param_2,2,0x1a,0,0);
      local_14 = FUN_0049eb44(param_1,param_2,2,0x1e,0,0);
      local_10 = FUN_0049eb44(param_1,param_2,2,0x18,0,0);
      FUN_0049f09b(param_2,local_24);
      piVar4 = local_24;
      piVar5 = local_44;
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar5 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar5 = piVar5 + 1;
      }
      local_44[3] = local_24[1] + local_8;
      iVar2 = *(int *)(param_2 + 0x98);
      while ((iVar2 < local_10 && (local_44[1] < local_24[3]))) {
        local_44[0] = local_24[0];
        local_44[2] = local_24[2];
        iVar3 = 0;
        if (0 < local_14) {
          do {
            iVar1 = FUN_00495d89(local_44,param_3,param_4);
            if (iVar1 != 0) {
              if (param_5 != (int *)0x0) {
                *param_5 = param_3 - local_44[0];
              }
              if (param_6 == (int *)0x0) {
                return iVar2;
              }
              *param_6 = param_4 - local_44[1];
              return iVar2;
            }
            FUN_00495c51(local_44,local_c,local_8);
            iVar3 = iVar3 + 1;
          } while (iVar3 < local_14);
        }
        iVar2 = iVar2 + 1;
      }
    }
  }
  return -1;
}

