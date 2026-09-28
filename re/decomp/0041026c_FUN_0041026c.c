// FUN_0041026c @ 0041026c size=746 sig=undefined FUN_0041026c() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0044ff28,FUN_0040f818,FUN_0040fc14,FUN_0040cdfc,FUN_00408b58,FUN_00471cec,FUN_0044ddf4,FUN_0040f974,FUN_00406424,FUN_00407d60,FUN_00472ca0,FUN_00410558,FUN_00475f80,FUN_0040f5e0,FUN_0040fb14,FUN_0040f8cc

void FUN_0041026c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined1 local_4c [4];
  int local_48 [11];
  int local_1c;
  int *local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_8 = *(int *)(param_2 + 0x1c);
  local_c = *(undefined4 *)(param_2 + 0x20);
  local_8 = FUN_0040fc14(param_1,(int)(char)(&DAT_004faf87)[local_8 * 0x24]);
  *(int *)(param_2 + 0x1c) = local_8;
  iVar2 = FUN_0044ff28(local_8);
  if (iVar2 == 0) {
    local_10 = FUN_0040f818(local_8,local_c,0);
    if (local_10 == 0) {
      local_10 = FUN_0040f818(local_8,local_c,1);
    }
    if (local_10 == 0) {
      local_10 = FUN_0040f8cc(local_8,local_c,0);
      if (local_10 == 0) {
        local_10 = FUN_0040f8cc(local_8,local_c,1);
      }
      if (local_10 == 0) {
        iVar2 = FUN_0040f5e0(local_8);
        uVar1 = *(undefined4 *)(&DAT_004b6f74 + iVar2 * 4);
        local_10 = FUN_0040fb14(local_8,local_c,0);
        if (local_10 == 0) {
          local_10 = FUN_0040fb14(local_8,local_c,1);
        }
        if (local_10 == 0) {
          FUN_0040f974(param_1,*(undefined4 *)(param_2 + 8),local_8,local_c);
        }
        else {
          FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),uVar1,
                       (int)*(short *)(local_10 + 0x1a),0xb,1);
        }
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
      else {
        FUN_0044ddf4(&DAT_0059f160 + param_1 * 0x2d8,local_8,local_4c);
        if ((local_1c == 0) ||
           ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[local_1c * 0x19]) != 0)) {
          iVar2 = FUN_00472ca0(local_10,local_48);
          if (iVar2 != -1) {
            local_48[0] = local_48[0] + iVar2;
          }
          local_14 = 1;
          iVar2 = 0;
          piVar4 = local_48;
          local_18 = &DAT_0059f16c + param_1 * 0xb6;
          do {
            if (*piVar4 != 0) {
              FUN_00408b58(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,
                           *piVar4,1);
              if (iVar2 == 0) {
                if (*local_18 < local_48[0]) {
                  local_14 = 0;
                }
              }
              else {
                iVar3 = FUN_00471cec(param_1,iVar2,*piVar4);
                if (iVar3 == 0) {
                  local_14 = 0;
                }
              }
            }
            iVar2 = iVar2 + 1;
            piVar4 = piVar4 + 1;
          } while (iVar2 < 0xb);
          if ((local_14 != 0) && (iVar2 = FUN_00406424(param_1,local_10), iVar2 != 0)) {
            iVar2 = FUN_00475f80(local_10,&DAT_0059f160 + param_1 * 0x2d8,local_8);
            if (iVar2 == 0) {
              FUN_00410558(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                           (int)*(short *)(local_10 + 0x1a),local_8,local_c,1);
            }
            *(undefined4 *)(param_2 + 0x10) = 1;
            return;
          }
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
        else {
          FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),local_1c,1)
          ;
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
      }
    }
    else {
      FUN_00410558(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                   (int)*(short *)(local_10 + 0x1a),local_8,local_c,1);
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
  }
  else {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  return;
}

