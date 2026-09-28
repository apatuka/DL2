// FUN_0040a710 @ 0040a710 size=392 sig=undefined FUN_0040a710() cc=unknown
// callers: FUN_0040aaa4
// callees: FUN_0040c6e8,FUN_0040c538,FUN_0040a60c,FUN_0040be04,FUN_0040c68c

void FUN_0040a710(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *local_14;
  
  iVar4 = (int)(char)(&DAT_0059f219)[param_1 * 0x2d8];
  if (*(int *)(&DAT_0052222c + param_1 * 4) != 0) {
    local_14 = &DAT_0059f161;
    iVar5 = 0;
    do {
      if ((((1 << ((byte)iVar5 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) != 0) &&
          (param_1 != iVar5)) && (*local_14 != '\0')) {
        iVar1 = FUN_0040a60c(param_1,iVar5,1);
        if (iVar1 != 0) {
          if (*(short *)(iVar1 + 0xa6c) < 2) {
            iVar2 = FUN_0040c6e8(param_1,3,iVar5);
            if (iVar2 != 0) {
              iVar3 = FUN_0040c538(iVar2,iVar1,0);
              if (iVar3 != 0) {
                *(int *)(iVar2 + 0x10) = iVar1;
                goto LAB_0040a82a;
              }
            }
            iVar2 = FUN_0040c68c(param_1,3,iVar1);
            if (iVar2 == 0) {
              FUN_0040be04(param_1,0xffffffff,iVar5,iVar1,3,iVar4);
            }
          }
          else {
            iVar2 = FUN_0040c6e8(param_1,0x13,iVar5);
            if (iVar2 != 0) {
              iVar3 = FUN_0040c538(iVar2,iVar1,0);
              if (iVar3 != 0) {
                *(int *)(iVar2 + 0x10) = iVar1;
                goto LAB_0040a82a;
              }
            }
            iVar2 = FUN_0040c68c(param_1,0x13,iVar1);
            if (iVar2 == 0) {
              FUN_0040be04(param_1,0xffffffff,iVar5,iVar1,0x13,iVar4);
            }
          }
        }
LAB_0040a82a:
        iVar1 = FUN_0040a60c(param_1,iVar5,0);
        if (iVar1 != 0) {
          iVar2 = FUN_0040c6e8(param_1,0xb,iVar5);
          if (iVar2 != 0) {
            iVar3 = FUN_0040c538(iVar2,iVar1,0);
            if (iVar3 != 0) {
              *(int *)(iVar2 + 0x10) = iVar1;
              goto LAB_0040a87e;
            }
          }
          iVar2 = FUN_0040c68c(param_1,0xb,iVar1);
          if (iVar2 == 0) {
            FUN_0040be04(param_1,0xffffffff,iVar5,iVar1,0xb,iVar4);
          }
        }
      }
LAB_0040a87e:
      iVar5 = iVar5 + 1;
      local_14 = local_14 + 0x2d8;
    } while (iVar5 < 7);
  }
  return;
}

