// FUN_00444b74 @ 00444b74 size=374 sig=undefined FUN_00444b74() cc=unknown
// callers: FUN_0043d184,CreateBldgHit,FUN_0043d594,FUN_0043da5c,FUN_00480d78,FUN_0043d8dc,FUN_0043d630,FUN_00480be0,FUN_004866fc,FUN_0043d860,FUN_0043d2d8,DestroyAnim,CreateHit
// callees: FUN_00445074

void FUN_00444b74(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)*(short *)(param_1 + 4);
  if ((param_2 != iVar1) && (*(short *)(param_1 + 4) = (short)param_2, DAT_00561a30 != DAT_00563fb4)
     ) {
    if (iVar1 < param_2) {
      iVar2 = *(int *)(param_1 + 0x38);
      if ((iVar2 != 0) && (param_2 <= *(short *)(iVar2 + 4))) {
        return;
      }
    }
    else {
      iVar2 = *(int *)(param_1 + 0x3c);
      if ((iVar2 != 0) && (*(short *)(iVar2 + 4) <= param_2)) {
        return;
      }
    }
    if (iVar2 != 0) {
      FUN_00445074((int)*(short *)(param_1 + 0xe),(int)*(short *)(param_1 + 0x10),
                   (int)*(short *)(param_1 + 0x12),(int)*(short *)(param_1 + 0x14));
      if (param_1 == DAT_00561a30) {
        DAT_00561a30 = *(int *)(param_1 + 0x38);
      }
      else {
        *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x38) = *(undefined4 *)(param_1 + 0x38);
      }
      if (param_1 == DAT_00563fb4) {
        DAT_00563fb4 = *(int *)(param_1 + 0x3c);
      }
      else {
        *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x3c) = *(undefined4 *)(param_1 + 0x3c);
      }
      if (iVar1 < param_2) {
        for (; (*(short *)(iVar2 + 4) < param_2 && (iVar2 != DAT_00563fb4));
            iVar2 = *(int *)(iVar2 + 0x38)) {
          FUN_00445074((int)*(short *)(iVar2 + 0xe),(int)*(short *)(iVar2 + 0x10),
                       (int)*(short *)(iVar2 + 0x12),(int)*(short *)(iVar2 + 0x14));
        }
      }
      else {
        while ((iVar2 != DAT_00561a30 && (param_2 < *(short *)(*(int *)(iVar2 + 0x3c) + 4)))) {
          FUN_00445074((int)*(short *)(iVar2 + 0xe),(int)*(short *)(iVar2 + 0x10),
                       (int)*(short *)(iVar2 + 0x12),(int)*(short *)(iVar2 + 0x14));
          iVar2 = *(int *)(iVar2 + 0x3c);
        }
      }
      if ((iVar2 == DAT_00563fb4) && (*(short *)(iVar2 + 4) < param_2)) {
        *(int *)(DAT_00563fb4 + 0x38) = param_1;
        *(int *)(param_1 + 0x3c) = DAT_00563fb4;
        *(undefined4 *)(param_1 + 0x38) = 0;
        DAT_00563fb4 = param_1;
      }
      else {
        if (iVar2 == DAT_00561a30) {
          DAT_00561a30 = param_1;
        }
        else {
          *(int *)(*(int *)(iVar2 + 0x3c) + 0x38) = param_1;
        }
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x3c);
        *(int *)(iVar2 + 0x3c) = param_1;
        *(int *)(param_1 + 0x38) = iVar2;
      }
    }
  }
  return;
}

