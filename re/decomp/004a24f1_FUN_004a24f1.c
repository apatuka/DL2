// FUN_004a24f1 @ 004a24f1 size=503 sig=undefined FUN_004a24f1() cc=unknown
// callers: 
// callees: FUN_0049f2bc,FUN_0049f83e,sprintf,strlen,FUN_004a5d23
// strings: \"%sID:%d\\r\\nX:%d y:%d\\r\\nW:%d H:%d\\r\\nMENU ID:%c%c%c%c\"

undefined4
FUN_004a24f1(int param_1,int param_2,int param_3,int param_4,int *param_5,undefined4 *param_6)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 local_188 [256];
  undefined1 local_88 [128];
  int local_8;
  
  if (param_4 == 1) {
    iVar2 = *(int *)(param_1 + 4);
    if ((iVar2 != 0) && ((*(byte *)(iVar2 + 0x1c) & 0x88) == 0)) {
      iVar4 = *(int *)(*(int *)(iVar2 + 300) + 4);
      do {
        piVar1 = (int *)FUN_0049f2bc(iVar2,param_2,param_3,iVar4);
        if (piVar1 == (int *)0x0) {
          return 0;
        }
        if ((((*(byte *)((int)piVar1 + 0x29) & 4) != 0) || ((DAT_0051dca4 & 2) != 0)) &&
           (0 < piVar1[0x41])) {
          *param_5 = iVar2;
          *param_6 = piVar1;
          return 1;
        }
        iVar4 = *piVar1;
      } while (iVar4 != 0);
    }
  }
  else if ((((param_4 == 2) && (param_5 != (int *)0x0)) && ((*(byte *)(param_5 + 7) & 0x88) == 0))
          && (param_6 != (undefined4 *)0x0)) {
    if ((*(byte *)((int)param_6 + 0x29) & 8) == 0) {
      if ((*(byte *)((int)param_6 + 0x29) & 0x10) != 0) {
        param_3 = param_5[3] + param_6[4] + param_6[5];
      }
    }
    else {
      param_3 = param_5[3] + param_6[4];
    }
    if ((*(byte *)((int)param_6 + 0x29) & 0x20) == 0) {
      if ((*(byte *)((int)param_6 + 0x29) & 0x40) != 0) {
        param_2 = param_5[2] + param_6[3] + param_6[6];
      }
    }
    else {
      param_2 = param_5[2] + param_6[3];
    }
    if (param_6[0x40] == 0) {
      puVar5 = (undefined1 *)param_6[0xd];
    }
    else {
      puVar5 = (undefined1 *)param_6[0x40];
    }
    if ((DAT_0051dca4 & 2) != 0) {
      if (((puVar5 == (undefined1 *)0x0) || (iVar2 = strlen(puVar5), iVar2 == 0)) ||
         (uVar3 = strlen(puVar5), 0x7f < uVar3)) {
        local_88[0] = 0;
      }
      else {
        sprintf(local_88,&DAT_0051e404,puVar5);
      }
      sprintf(local_188,s__sID__d_X__d_y__d_W__d_H__d_MENU_0051e409,local_88,param_6[0xc],param_6[3]
              ,param_6[4],param_6[6],param_6[5],(int)(char)param_5[0xc],
              (int)(char)((uint)param_5[0xc] >> 8),(int)(char)((uint)param_5[0xc] >> 0x10),
              (int)(char)((uint)param_5[0xc] >> 0x18));
      puVar5 = local_188;
    }
    local_8 = FUN_004a5d23(puVar5,param_2,param_3,param_5[0xf],param_5[0x18],
                           (int)(param_6[10] & 0x7800) >> 0xb);
    if (local_8 != 0) {
      *(int *)(local_8 + 0x24) = param_5[9];
      FUN_0049f83e(local_8);
    }
    return 1;
  }
  return 0;
}

