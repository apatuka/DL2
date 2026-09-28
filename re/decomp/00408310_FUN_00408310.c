// FUN_00408310 @ 00408310 size=570 sig=undefined FUN_00408310() cc=unknown
// callers: FUN_0040854c
// callees: FUN_00408b58,FUN_0040917c,FUN_00471cec,FUN_0047597c,FUN_00475a60,FUN_0044de9c,FUN_00472ca0,FUN_004091fc,FUN_0040cdfc

void FUN_00408310(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined1 local_88 [8];
  int local_80 [11];
  undefined1 local_54 [4];
  int local_50 [12];
  int *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  int local_8;
  
  iVar5 = *(int *)(param_2 + 0x1c);
  local_8 = *(int *)(param_2 + 0x20);
  iVar4 = 0;
  if ((iVar5 != -1) && (local_8 != -1)) {
    iVar4 = (&DAT_005a4524)[iVar5 * 0x2b7 + local_8 * 0xd];
  }
  if ((iVar4 != 0) && (*(char *)(iVar4 + 5) == '\x12')) {
    local_c = &DAT_005a43d0 + iVar5 * 0xadc;
    local_10 = FUN_0040917c(param_1,(int)*(short *)(iVar4 + 8),(int)*(char *)(iVar4 + 4));
    if (*(char *)(iVar4 + 4) == local_10) {
      iVar5 = FUN_004091fc(param_1,(int)*(short *)(iVar4 + 8),(int)*(char *)(iVar4 + 4));
      if (iVar5 == 0) {
        *(undefined4 *)(param_2 + 0x10) = 1;
      }
      else {
        FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar5,1);
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
    }
    else {
      FUN_0044de9c(&DAT_0059f160 + param_1 * 0x2d8,local_10,(int)(char)local_c[0x21],local_54);
      FUN_0044de9c(&DAT_0059f160 + param_1 * 0x2d8,(int)*(char *)(iVar4 + 4),
                   (int)(char)local_c[0x21],local_88);
      iVar5 = 1;
      piVar3 = local_80;
      piVar1 = local_50;
      do {
        piVar1 = piVar1 + 1;
        local_14 = *piVar1 - (*piVar3 >> 1);
        local_18 = 0;
        if (local_14 < 0) {
          piVar2 = &local_18;
        }
        else {
          piVar2 = &local_14;
        }
        *piVar1 = *piVar2;
        iVar5 = iVar5 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar5 < 0xb);
      iVar5 = FUN_00472ca0(local_c,local_50);
      if (iVar5 != -1) {
        local_50[0] = local_50[0] + iVar5;
      }
      local_1c = 1;
      iVar5 = 0;
      piVar3 = local_50;
      local_20 = &DAT_0059f16c + param_1 * 0xb6;
      do {
        if (*piVar3 != 0) {
          FUN_00408b58(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar5,
                       *piVar3,1);
          if (iVar5 == 0) {
            if (*local_20 < local_50[0]) {
              local_1c = 0;
            }
          }
          else {
            iVar4 = FUN_00471cec(param_1,iVar5,*piVar3);
            if (iVar4 == 0) {
              local_1c = 0;
            }
          }
        }
        iVar5 = iVar5 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar5 < 0xb);
      if (local_1c == 0) {
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
      else {
        FUN_00475a60(local_c,local_8,0);
        FUN_0047597c(local_c,local_10,local_8);
      }
    }
  }
  return;
}

