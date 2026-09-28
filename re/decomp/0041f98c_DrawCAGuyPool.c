// DrawCAGuyPool @ 0041f98c size=553 sig=undefined DrawCAGuyPool() cc=unknown
// callers: FUN_00420954
// callees: DebugMessage,FUN_0049aa64,FUN_00490ab3,FUN_0049a93f,FUN_0049a8ed,FUN_0049f22b,FUN_00496e80,FUN_0048c85e,FUN_00490796,FUN_0041ba04,FUN_00498aab,FUN_0048c434
// strings: \"gpColonyAssistant NULL in DrawCAGuyPool()\"

/* auto-named from string evidence: DrawCAGuyPool */

int DrawCAGuyPool(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_ESI;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined1 local_20 [16];
  
  if (DAT_004b7a14 == 0) {
    DebugMessage(s_gpColonyAssistant_NULL_in_DrawCA_004b7a87);
    unaff_ESI = 0;
  }
  else {
    local_2c = DAT_0051bddc;
    FUN_0048c434(*(undefined4 *)(DAT_004b7a14 + 0x3c));
    if (DAT_0053b8ac < 0x1c) {
      local_28 = (&DAT_00564224)[DAT_0053b8ac * 6];
      local_24 = (&DAT_00564224)[DAT_0053b8ac * 6] + *(int *)(&DAT_00564228 + DAT_0053b8ac * 0x18) +
                 *(int *)(&DAT_0056422c + DAT_0053b8ac * 0x18);
      if (0x32 < local_24) {
        local_24 = 0x32;
      }
      iVar3 = 0;
      if (0 < local_24) {
        do {
          unaff_ESI = 0;
          iVar1 = iVar3;
          if (0xb < iVar3) {
            if (iVar3 < 0x19) {
              unaff_ESI = 1;
              iVar1 = iVar3 + -0xc;
            }
            else if (iVar3 < 0x26) {
              unaff_ESI = 2;
              iVar1 = iVar3 + -0x19;
            }
            else {
              unaff_ESI = 3;
              iVar1 = iVar3 + -0x26;
            }
          }
          FUN_0041ba04(&local_34,&local_30,unaff_ESI,iVar1);
          FUN_0049a8ed();
          FUN_0049f22b(DAT_004b7a14,local_20);
          FUN_0049aa64(local_20);
          if ((&DAT_004b7760)[unaff_ESI * 0xd + iVar1] == 1) {
            uVar4 = 0x3f4;
          }
          else if (iVar3 < local_28) {
            uVar4 = 0x3f0;
            (&DAT_004b7760)[unaff_ESI * 0xd + iVar1] = 2;
          }
          else if (iVar3 < *(int *)(&DAT_00564228 + DAT_0053b8ac * 0x18) + local_28) {
            uVar4 = 0x3f1;
            (&DAT_004b7760)[unaff_ESI * 0xd + iVar1] = 3;
          }
          else {
            uVar4 = 0x3f3;
            (&DAT_004b7760)[unaff_ESI * 0xd + iVar1] = 3;
          }
          iVar1 = FUN_00490ab3(0,0x47414d49,0x31305542,0,0);
          if (iVar1 != 0) {
            uVar2 = FUN_00498aab(iVar1,1);
            FUN_00496e80(uVar2,uVar4,(int)(char)PTR_DAT_004d5988[2],0,local_34,local_30,0xffffffff);
            FUN_00498aab(iVar1,0);
            FUN_00490796(iVar1,0);
          }
          FUN_0049a93f();
          iVar3 = iVar3 + 1;
        } while (iVar3 < local_24);
      }
      if (((DAT_004b7a14 != 0) && (*(int *)(DAT_004b7a14 + 0x3c) != 0)) &&
         ((*(byte *)(DAT_004b7a14 + 0x1c) & 2) != 0)) {
        FUN_0048c85e(*(undefined4 *)(DAT_004b7a14 + 0x3c),&DAT_0065e644,local_20,local_20,0,
                     &DAT_0065e580,0);
      }
      FUN_0048c434(local_2c);
    }
  }
  return unaff_ESI;
}

