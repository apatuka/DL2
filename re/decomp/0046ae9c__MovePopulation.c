// _MovePopulation @ 0046ae9c size=471 sig=undefined _MovePopulation() cc=unknown
// callers: FUN_0047636c,FUN_00476448
// callees: FUN_0044bea8,FUN_0047ca98,FUN_0044c238,FUN_0044ba18,DebugMessage,FUN_0046b0e4,FUN_0044bddc,FUN_0044d1a4
// strings: \"Invalid building in _MovePopulation()\"

/* auto-named from string evidence: _MovePopulation */

undefined4
_MovePopulation(int param_1,int param_2,int param_3,int param_4,short param_5,short param_6)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  cVar2 = *(char *)(param_1 + 0x20);
  if (((cVar2 != -1) && (param_2 != param_1)) && (cVar2 == *(char *)(param_2 + 0x20))) {
    iVar3 = param_3 + 3;
    if (iVar3 < 0) {
      iVar3 = param_3 + 6;
    }
    if (((iVar3 >> 2 <= (int)(&DAT_0059f16c)[cVar2 * 0xb6]) &&
        (param_3 <= *(short *)(param_1 + 0x30))) &&
       ((iVar3 = FUN_0046b0e4(param_2), *(short *)(param_2 + 0x30) + param_3 <= iVar3 &&
        (iVar3 = FUN_0044d1a4(param_2,0x11,0), iVar3 != -1)))) {
      iVar3 = param_3 + 3;
      if (iVar3 < 0) {
        iVar3 = param_3 + 6;
      }
      (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] =
           (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] - (iVar3 >> 2);
      *(char *)(param_2 + 0x27) =
           (char)(((int)*(short *)(param_2 + 0x30) * (int)*(char *)(param_2 + 0x27) +
                  param_3 * *(char *)(param_1 + 0x27)) / (param_3 + *(short *)(param_2 + 0x30)));
      if ((*(byte *)(param_1 + 0x1c) & 0x20) != 0) {
        FUN_0047ca98(1,param_2,0xfffffffc);
      }
      *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) - (short)param_3;
      *(short *)(param_2 + 0x30) = *(short *)(param_2 + 0x30) + (short)param_3;
      if (param_5 != -1) {
        iVar3 = *(int *)(param_1 + 0x154 + param_5 * 0x34);
        if (iVar3 == 0) {
          DebugMessage(s_Invalid_building_in__MovePopulat_004d5870);
          return 0;
        }
        if (param_6 == -1) {
          iVar4 = FUN_0044ba18(iVar3);
          if (param_3 / 100 <= iVar4) {
            FUN_0044bddc(iVar3,-(param_3 / 100));
          }
        }
        else if (param_3 / 100 <= *(int *)(iVar3 + 0x18 + param_6 * 4)) {
          piVar1 = (int *)(iVar3 + 0x18 + param_6 * 4);
          *piVar1 = *piVar1 - param_3 / 100;
        }
      }
      if (param_4 == 0) {
        if (param_5 == -1) {
          FUN_0044c238(param_1);
        }
        FUN_0044c238(param_2);
      }
      else {
        if (param_5 == -1) {
          FUN_0044bea8(param_1);
        }
        FUN_0044bea8(param_2);
      }
      return 1;
    }
  }
  return 0;
}

