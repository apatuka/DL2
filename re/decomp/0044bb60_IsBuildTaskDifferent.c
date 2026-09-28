// IsBuildTaskDifferent @ 0044bb60 size=264 sig=undefined IsBuildTaskDifferent() cc=unknown
// callers: FUN_0044f3f0,FUN_0044bd0c
// callees: FUN_0044eeb4,FUN_0044c718,DebugMessage
// strings: \"Invalid building in IsBuildTaskDifferent()\"

/* auto-named from string evidence: IsBuildTaskDifferent */

bool IsBuildTaskDifferent(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  int local_14;
  int local_10;
  
  cVar1 = *(char *)(param_1 + 0x2c + param_2);
  if (param_1 == 0) {
    DebugMessage(s_Invalid_building_in_IsBuildTaskD_004c5fdd);
    bVar6 = false;
  }
  else {
    iVar5 = *(short *)(param_1 + 8) * 0xadc;
    cVar2 = (&DAT_005a43f0)[iVar5];
    local_14 = 0;
    local_10 = 0;
    iVar3 = FUN_0044eeb4(&DAT_0059f160 + cVar2 * 0x2d8,&DAT_005a43d0 + iVar5,
                         (int)*(char *)(param_1 + 7),param_2,param_3);
    iVar5 = FUN_0044eeb4(&DAT_0059f160 + cVar2 * 0x2d8,&DAT_005a43d0 + iVar5,
                         (int)*(char *)(param_1 + 7),param_2,param_4);
    if (cVar1 == '\x02') {
      if (iVar3 != 0) {
        local_10 = (*(short *)(param_1 + 0x14) + iVar3 + -1) / iVar3;
      }
      if (iVar5 != 0) {
        local_14 = (*(short *)(param_1 + 0x14) + iVar5 + -1) / iVar5;
      }
    }
    else {
      if (iVar3 != 0) {
        iVar4 = FUN_0044c718(param_1);
        local_10 = ((iVar4 - *(short *)(param_1 + 0x16)) + iVar3 + -1) / iVar3;
      }
      if (iVar5 != 0) {
        iVar3 = FUN_0044c718(param_1);
        local_14 = ((iVar3 - *(short *)(param_1 + 0x16)) + iVar5 + -1) / iVar5;
      }
    }
    bVar6 = local_10 != local_14;
  }
  return bVar6;
}

