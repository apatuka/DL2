// FUN_00489ae1 @ 00489ae1 size=349 sig=undefined FUN_00489ae1() cc=unknown
// callers: 
// callees: FUN_004899fd,FUN_00489524,FUN_00489572,FUN_00498ba9,FUN_00495a77,FUN_004895a4,FUN_00495a4a,_SmackOpen@12,FUN_0048f774

int FUN_00489ae1(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  uint local_c;
  
  local_c = 0;
  piVar4 = (int *)0x0;
  iVar1 = FUN_00498ba9(0x8c);
  if (iVar1 != 0) {
    FUN_0048f774(iVar1,0x8c,0);
    piVar2 = (int *)FUN_00498ba9(0x10);
    if (piVar2 != (int *)0x0) {
      FUN_0048f774(piVar2,0x10,0);
      *(int **)(iVar1 + 0x1c) = piVar2;
      FUN_00495a77(iVar1);
      *(code **)(iVar1 + 0x58) = FUN_00489524;
      *(code **)(iVar1 + 0x5c) = FUN_00489538;
      *(code **)(iVar1 + 0x54) = FUN_00489572;
      *(code **)(iVar1 + 0x60) = FUN_004895a4;
      *(code **)(iVar1 + 0x78) = FUN_004895ce;
      *(code **)(iVar1 + 0x40) = FUN_004899fd;
      *(code **)(iVar1 + 0x68) = FUN_00489a1c;
      *(code **)(iVar1 + 0x6c) = FUN_00489a43;
      *(code **)(iVar1 + 0x70) = FUN_00489a6a;
      *(code **)(iVar1 + 0x74) = FUN_00489ab8;
      *(code **)(iVar1 + 0x7c) = FUN_0048997c;
      *(code **)(iVar1 + 0x80) = FUN_004899ca;
      *(code **)(iVar1 + 0x84) = FUN_004897cb;
      *(code **)(iVar1 + 0x88) = FUN_004897ea;
      if (param_2 == 2) {
        local_c = 0x1000;
        piVar4 = param_1;
      }
      else if ((param_2 == 4) && (*param_1 == 2)) {
        local_c = 0x1000;
        piVar4 = (int *)param_1[1];
      }
      if (piVar4 != (int *)0x0) {
        param_1 = piVar4;
      }
      iVar3 = _SmackOpen_12(param_1,local_c | 0xfe000,0xffffffff);
      if (iVar3 == 0) {
        (**(code **)(iVar1 + 0x40))(iVar1);
        iVar1 = 0;
      }
      else {
        *piVar2 = iVar3;
        piVar2[3] = (int)piVar4;
        (**(code **)(iVar1 + 0x58))(iVar1,1);
        (**(code **)(iVar1 + 0x54))(iVar1,iVar1 + 0x10,iVar1 + 0xc);
        if (DAT_0051e080 != 0) {
          FUN_00495a4a(iVar1,param_4);
        }
        (**(code **)(iVar1 + 0x60))(iVar1,0,0,0,0);
      }
    }
  }
  return iVar1;
}

