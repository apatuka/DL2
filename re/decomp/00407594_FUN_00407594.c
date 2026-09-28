// FUN_00407594 @ 00407594 size=278 sig=undefined FUN_00407594() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040bfb4,FUN_00416e70,FUN_0040beb4,FUN_0040c668,FUN_0040c5cc,FUN_0040bbf4

void FUN_00407594(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  sVar1 = *(short *)(param_1 + 10);
  sVar2 = *(short *)(param_1 + 8);
  iVar3 = *(int *)(param_1 + 0x10);
  FUN_0040bfb4(param_1,1);
  FUN_0040bfb4(param_1,0xf);
  if ((iVar3 == 0) || ((int)*(char *)(iVar3 + 0x20) != (int)sVar2)) {
    FUN_0040beb4(param_1);
  }
  else {
    FUN_0040bbf4(param_1,0,0);
    iVar3 = FUN_0040c5cc(param_1);
    if (iVar3 != 0) {
      iVar3 = (int)(char)(&DAT_0059f162)[sVar1 * 0x2d8];
      iVar4 = FUN_0040c668(param_1);
      if (iVar4 != 0) {
        iVar5 = FUN_00416e70(iVar4,0x13,iVar3);
        if (iVar5 == 0) {
          iVar5 = FUN_00416e70(iVar4,3,iVar3);
          if (iVar5 == 0) {
            iVar5 = FUN_00416e70(iVar4,2,iVar3);
            if (iVar5 == 0) {
              iVar5 = FUN_00416e70(iVar4,6,iVar3);
              if (iVar5 == 0) {
                iVar5 = FUN_00416e70(iVar4,5,iVar3);
                if (iVar5 == 0) {
                  iVar3 = FUN_00416e70(iVar4,4,iVar3);
                  if (iVar3 != 0) {
                    FUN_0040bfb4(param_1,4);
                  }
                }
                else {
                  FUN_0040bfb4(param_1,5);
                }
              }
              else {
                FUN_0040bfb4(param_1,6);
              }
            }
            else {
              FUN_0040bfb4(param_1,2);
            }
          }
          else {
            FUN_0040bfb4(param_1,3);
          }
        }
        else {
          FUN_0040bfb4(param_1,0x13);
        }
      }
    }
  }
  return;
}

