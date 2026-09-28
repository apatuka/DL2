// FUN_0041acf8 @ 0041acf8 size=755 sig=undefined FUN_0041acf8() cc=unknown
// callers: FUN_0041afec,FUN_0041b1c8
// callees: FUN_0044d440,FUN_0049eb44,FUN_0041a610,FUN_0044d3f4,FUN_0044feec,FUN_00471f5c,SetItemStats,FUN_0044d1a4,sprintf
// strings: \"Apartment Complex\"

void FUN_0041acf8(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined **ppuVar5;
  int local_f8;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  int local_e4;
  undefined4 local_e0;
  undefined1 local_d8 [200];
  
  bVar1 = false;
  local_f0 = 0;
  DAT_004b76f0 = 0;
  local_ec = 0x31305542;
  local_e8 = 9000;
  local_e4 = 0;
  local_e0 = 0;
  iVar4 = 0x2c;
  if (DAT_004d5aa0 != '\0') {
    iVar4 = 0x2f;
  }
  iVar3 = 1;
  ppuVar5 = &PTR_s_Housing_004f9dee;
  if (iVar4 != 0) {
    do {
      if ((DAT_004d5aa0 != '\0') || (((iVar3 != 2 && (iVar3 != 3)) && (iVar3 != 0x16)))) {
        if (*(char *)(DAT_0053b334 + 0x21) != '\0') {
          iVar2 = FUN_0044d440(iVar3);
          if (iVar2 != 0) goto LAB_0041af09;
        }
        if (*(char *)(DAT_0053b334 + 0x21) == '\0') {
          iVar2 = FUN_0044d3f4(iVar3);
          if ((iVar2 == 0) && ((DAT_004d5aa0 == '\0' || ((iVar3 != 0x26 && (iVar3 != 0x2f))))))
          goto LAB_0041af09;
        }
        iVar2 = FUN_0044feec(iVar3);
        if (iVar2 == 0) {
          if ((DAT_004d5aa0 != '\0') && (*(char *)(DAT_0053b334 + 0x21) == '\0')) {
            iVar2 = FUN_0044d1a4(DAT_0053b334,0x14,0);
            if (iVar2 == -1) {
              iVar2 = FUN_0044d3f4(iVar3);
              if (iVar2 != 0) goto LAB_0041af09;
            }
          }
          if (iVar3 != 0x27) {
            if (DAT_0053b268 != '\0') {
              iVar2 = FUN_00471f5c(iVar3,DAT_0053b334);
              if (iVar2 != 0) goto LAB_0041af09;
            }
            (&DAT_0053b26c)[DAT_004b76f0] = iVar3;
            DAT_004b76f0 = DAT_004b76f0 + 1;
            sprintf(local_d8,&DAT_004b7700,*ppuVar5);
            iVar2 = FUN_0049eb44(DAT_004b76f8,6,1,0x26,0xffffffff,local_d8);
            if (iVar2 != 0) {
              local_e4 = (int)*(char *)((int)ppuVar5 + 6);
              if (((iVar3 == 1) || (iVar3 == 2)) || (iVar3 == 3)) {
                local_e4 = local_e4 + (char)PTR_DAT_004d5988[2] * 3;
              }
              if (((iVar3 == 0x17) || (iVar3 == 0x25)) || ((iVar3 == 0x27 || (iVar3 == 0x26)))) {
                local_e4 = local_e4 + (char)PTR_DAT_004d5988[2];
              }
              FUN_0049eb44(DAT_004b76f8,6,1,0x23,iVar2 + -1,local_d8);
              FUN_0049eb44(DAT_004b76f8,6,1,0x24,iVar2 + -1,&local_f0);
              if (iVar3 == DAT_004b76fc) {
                bVar1 = true;
                local_f8 = iVar2 + -1;
              }
            }
          }
        }
      }
LAB_0041af09:
      iVar3 = iVar3 + 1;
      ppuVar5 = (undefined **)((int)ppuVar5 + 0x32);
    } while (iVar3 <= iVar4);
  }
  FUN_0049eb44(DAT_004b76f8,7,1,0x31,6,1);
  if (iVar3 < 6) {
    FUN_0049eb44(DAT_004b76f8,7,1,10,1,0);
  }
  else {
    FUN_0049eb44(DAT_004b76f8,7,1,10,0,0);
  }
  FUN_0049eb44(DAT_004b76f8,6,1,0x34,1,0);
  if (bVar1) {
    FUN_0049eb44(DAT_004b76f8,6,1,0x1b,local_f8,0);
    FUN_0049eb44(DAT_004b76f8,6,1,0x21,local_f8,1);
    FUN_0041a610();
  }
  else if (iVar3 < 1) {
    DAT_004b76fc = 0;
  }
  else {
    FUN_0049eb44(DAT_004b76f8,6,1,0x1b,0,0);
    FUN_0041a610();
  }
  SetItemStats();
  return;
}

