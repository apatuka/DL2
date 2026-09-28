// FUN_004a0f18 @ 004a0f18 size=225 sig=undefined FUN_004a0f18() cc=unknown
// callers: FUN_004a2078
// callees: FUN_0049a93f,FUN_0049ea99,FUN_00495162,FUN_004a0e79,FUN_0049f09b,FUN_0048de03,FUN_0049551a,FUN_0049a8ed,FUN_0049372b
// strings: \"DrawSMenuItem, index %d, id %d, time:%d\\r\\n\"

void FUN_004a0f18(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_ESI;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (0 < *(int *)(param_1 + 0x104)) {
    FUN_0049a8ed();
    if (((DAT_0051dca4 & 2) != 0) && ((*(byte *)(param_1 + 0x2a) & 0x80) != 0)) {
      FUN_0049a8ed();
      FUN_0049f09b(param_1,&local_14);
      FUN_0049372b(local_14,local_10,local_c + -1,local_8 + -1,0x80ffffff);
      FUN_0049a93f();
    }
    if ((DAT_0051e388 & 2) != 0) {
      unaff_ESI = FUN_0048de03();
    }
    if (*(int *)(param_1 + 0x40) == 0) {
      iVar1 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_004a0e79(uVar2,iVar1);
    }
    else {
      iVar1 = (**(code **)(param_1 + 0x40))(param_1,3,0,0);
      if (iVar1 == 0) {
        iVar1 = param_1;
        uVar2 = FUN_0049ea99(param_1);
        FUN_004a0e79(uVar2,iVar1);
      }
    }
    if ((DAT_0051e388 & 2) != 0) {
      iVar1 = FUN_0048de03();
      if (0 < iVar1 - unaff_ESI) {
        iVar3 = FUN_0049ea99(param_1);
        uVar2 = FUN_0049551a(*(undefined4 *)(iVar3 + 300),param_1);
        FUN_00495162(s_DrawSMenuItem__index__d__id__d__t_0051e3b4,uVar2,
                     *(undefined4 *)(param_1 + 0x30),iVar1 - unaff_ESI);
      }
    }
    FUN_0049a93f();
  }
  return;
}

