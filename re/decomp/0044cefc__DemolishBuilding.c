// _DemolishBuilding @ 0044cefc size=311 sig=undefined _DemolishBuilding() cc=unknown
// callers: FUN_00486b74,NetDemolishBuilding,FUN_0046e39c,FUN_00475a60
// callees: FUN_0044bea8,DebugMessage,FUN_0047dfdc,FUN_0044df30,FUN_0044de9c,_DeleteBuilding,FUN_00450320,FUN_0044b8f8
// strings: \"Invalid building in _DemolishBuilding\"

/* auto-named from string evidence: _DemolishBuilding */

void _DemolishBuilding(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined1 local_38 [4];
  int local_34 [12];
  
  iVar1 = *(int *)(param_2 + 0x154 + param_3 * 0x34);
  if ((DAT_0058f1fc == 0) || (iVar1 != 0)) {
    if (iVar1 != 0) {
      if ((*(char *)(iVar1 + 5) == '\v') &&
         (*(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) & 0xffffffef, DAT_004d5aa0 == '\0'))
      {
        iVar2 = FUN_00450320();
        if (iVar2 == 0) {
          FUN_0044b8f8(param_1,param_2);
        }
      }
      if ((*(byte *)(iVar1 + 2) & 2) == 0) {
        iVar2 = 0;
        piVar3 = local_34;
        piVar4 = (int *)(iVar1 + 0x3e);
        do {
          *piVar3 = *piVar4;
          iVar2 = iVar2 + 1;
          piVar3 = piVar3 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar2 < 0xb);
      }
      else if (*(char *)(iVar1 + 4) == '%') {
        FUN_0044df30(iVar1,local_38);
      }
      else {
        FUN_0044de9c(param_1,(int)*(char *)(iVar1 + 4),(int)*(char *)(param_2 + 0x21),local_38);
      }
      if (DAT_004d5aa0 == '\0') {
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + (int)(short)(local_34[0] >> 1);
      }
      if (DAT_004d5aa0 == '\0') {
        iVar2 = 1;
        piVar3 = (int *)(param_2 + 0x3e);
        piVar4 = local_34;
        do {
          piVar4 = piVar4 + 1;
          iVar2 = iVar2 + 1;
          *piVar3 = *piVar3 + (int)(short)(*piVar4 >> 1);
          piVar3 = piVar3 + 1;
        } while (iVar2 < 0xb);
      }
      _DeleteBuilding(param_2,param_3);
      FUN_0044bea8(param_2);
      FUN_0047dfdc(&DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc);
    }
  }
  else {
    DebugMessage(s_Invalid_building_in__DemolishBui_004c60d9);
  }
  return;
}

