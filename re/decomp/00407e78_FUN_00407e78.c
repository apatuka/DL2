// FUN_00407e78 @ 00407e78 size=1033 sig=undefined FUN_00407e78() cc=unknown
// callers: FUN_004059bc
// callees: FUN_00402cc0,FUN_00408b58,FUN_00471cec,FUN_0040401c,FUN_0044de9c,FUN_0040a524,FUN_0044d1a4,FUN_00407dfc,FUN_0040cdfc,FUN_00408288,FUN_00402d58,FUN_00472ca0,FUN_00406424,FUN_00407d60,FUN_00403fd8

void FUN_00407e78(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  undefined1 local_4c [4];
  int local_48 [11];
  int local_1c;
  int *local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = *(int *)(param_2 + 0x1c);
  local_8 = *(int *)(param_2 + 0x20);
  local_c = *(int *)(param_2 + 0x24);
  if (local_8 == -1) {
    iVar1 = FUN_0040401c((int)(char)(&DAT_004f9dc3)[iVar2 * 0x32]);
  }
  else {
    iVar1 = FUN_00403fd8(&DAT_005a43d0 + local_8 * 0xadc,(int)(char)(&DAT_004f9dc3)[iVar2 * 0x32]);
  }
  if (iVar1 == 0) {
    local_10 = 0;
    local_10 = FUN_00402cc0(param_1,iVar2,local_8,local_c);
    iVar1 = iVar2;
    if ((local_10 == 0) && ((&DAT_004f9dc5)[iVar2 * 0x32] == '\x02')) {
      iVar3 = iVar2 + 1;
      pcVar4 = &DAT_004f9dc3 + iVar3 * 0x32;
      while (((iVar1 = iVar2, iVar3 < 0x30 && ((&DAT_004f9dc3)[iVar2 * 0x32] == *pcVar4)) &&
             (((pcVar4[0x20] != 0 &&
               ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[pcVar4[0x20] * 0x19]) ==
                0)) || (local_10 = FUN_00402cc0(param_1,iVar3,local_8,local_c), iVar1 = iVar3,
                       local_10 == 0))))) {
        iVar3 = iVar3 + 1;
        pcVar4 = pcVar4 + 0x32;
      }
    }
    if (local_10 == 0) {
      if (((&DAT_004f9dc3)[iVar1 * 0x32] == '\x01') && (iVar1 != 0x29)) {
        FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),0x29,
                     0xffffffff,0xc,1);
      }
      else if (((&DAT_004f9dc3)[iVar1 * 0x32] == '\x03') && (iVar1 != 0x2a)) {
        FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),0x2a,
                     0xffffffff,0xf,1);
      }
      else if (local_8 == -1) {
        FUN_0040a524(param_1,(int)(char)(&DAT_0059f1bf)
                                        [*(int *)(param_2 + 4) * 0x5a + param_1 * 0x2d8],
                     *(undefined4 *)(&DAT_004b627c + local_c * 4));
      }
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
    else if (((*(char *)(local_10 + 0x21) == '\0') && ((&DAT_004f9dc3)[iVar1 * 0x32] != '\x12')) &&
            (iVar2 = FUN_0044d1a4(local_10,0x12,0), iVar2 == -1)) {
      FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar1,local_8,
                   local_c,1);
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
    else {
      FUN_0044de9c(&DAT_0059f160 + param_1 * 0x2d8,iVar1,(int)*(char *)(local_10 + 0x21),local_4c);
      if ((local_1c == 0) ||
         ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[local_1c * 0x19]) != 0)) {
        iVar2 = FUN_00472ca0(local_10,local_48);
        if (iVar2 != -1) {
          local_48[0] = local_48[0] + iVar2;
        }
        local_14 = 1;
        iVar2 = 0;
        piVar5 = local_48;
        local_18 = &DAT_0059f16c + param_1 * 0xb6;
        do {
          if (*piVar5 != 0) {
            iVar3 = FUN_00407dfc(iVar1,iVar2);
            if (iVar3 == 0) {
              FUN_00408b58(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,
                           *piVar5,1);
            }
            if (iVar2 == 0) {
              if (*local_18 < local_48[0]) {
                local_14 = 0;
              }
            }
            else {
              iVar3 = FUN_00471cec(param_1,iVar2,*piVar5);
              if (iVar3 == 0) {
                local_14 = 0;
              }
            }
          }
          iVar2 = iVar2 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar2 < 0xb);
        if ((local_14 == 0) || (iVar2 = FUN_00406424(param_1,local_10), iVar2 == 0)) {
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
        else {
          iVar2 = FUN_00402d58(param_1,local_10,iVar1,local_c);
          if (iVar2 != 0) {
            *(undefined1 *)(iVar2 + 0xe) = *(undefined1 *)(param_2 + 4);
            FUN_00408288(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                         (int)*(short *)(iVar2 + 8),(int)*(char *)(iVar2 + 7),1);
          }
          *(undefined4 *)(param_2 + 0x10) = 1;
        }
      }
      else {
        FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),local_1c,1);
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
    }
  }
  else {
    FUN_00408288(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                 (int)*(short *)(iVar1 + 8),(int)*(char *)(iVar1 + 7),1);
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  return;
}

