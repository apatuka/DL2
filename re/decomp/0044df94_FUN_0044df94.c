// FUN_0044df94 @ 0044df94 size=229 sig=undefined FUN_0044df94() cc=unknown
// callers: FUN_00475f80,ProduceUnits,FUN_00475ed4
// callees: FUN_0044ddf4,memset,FUN_00484da8,FUN_0044bea8,FUN_004722e0,FUN_0044b5bc

int FUN_0044df94(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_6c [2];
  undefined2 local_6a;
  undefined1 local_68 [44];
  undefined2 local_3c [26];
  int local_8;
  
  uVar2 = 0;
  local_8 = -1;
  switch((&DAT_004faf87)[param_3 * 0x24]) {
  case 1:
  case 2:
    uVar2 = 1;
    break;
  case 3:
  case 0xd:
    uVar2 = 3;
    break;
  case 4:
  case 5:
  case 0xc:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    uVar2 = 2;
    break;
  case 6:
  case 7:
  case 8:
  case 0xb:
    uVar2 = 5;
    break;
  case 9:
    uVar2 = 4;
  }
  memset(local_6c,0,0x30);
  iVar1 = FUN_0044b5bc(param_1,uVar2);
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else if (((param_3 != 0x19) && (param_3 != 0x1f)) || (100 < *(short *)(param_1 + 0x30))) {
    FUN_0044ddf4(param_2,param_3,local_3c);
    local_8 = FUN_004722e0(param_2,param_1,local_3c,local_68);
    if (local_8 == 0) {
      local_6c[0] = (undefined1)param_3;
      local_6a = local_3c[0];
      FUN_00484da8(iVar1,local_6c);
      if ((param_3 == 0x19) || (param_3 == 0x1f)) {
        *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) + -100;
        FUN_0044bea8(param_1);
      }
    }
  }
  return local_8;
}

