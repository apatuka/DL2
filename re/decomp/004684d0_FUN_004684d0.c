// FUN_004684d0 @ 004684d0 size=695 sig=undefined FUN_004684d0() cc=unknown
// callers: 
// callees: FUN_0046ca40,FUN_00471634,FUN_00463a74,FUN_0042c41c,FUN_00461c68,FUN_00466ddc,memcpy
// strings: \".\\\\deadlock.ini\"

undefined4 FUN_004684d0(void)

{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined *puVar6;
  char *pcVar7;
  uint local_1c;
  undefined1 local_18 [10];
  undefined1 local_e;
  undefined1 local_c;
  undefined1 local_b [7];
  
  memcpy(&DAT_0051a8cc,&DAT_0051accc,0x3b0);
  FUN_00463a74();
  if (DAT_004d59a8 == 0) {
    iVar1 = FUN_0042c41c();
  }
  else {
    FUN_00471634(s___deadlock_ini_004d5277,local_18,&local_1c,&DAT_005597d5,0x104);
    if ((DAT_004d59a8 & 4) != 0) {
      DAT_004d5a88 = 1;
      iVar1 = FUN_00461c68(&DAT_005597d5);
      if (iVar1 != 0) {
        return 0x40;
      }
      DAT_004d59a8 = 0;
      DAT_004d5a88 = 0;
      return 0x35;
    }
    if (local_1c == 4) {
      DAT_004d5b1c = local_c;
      DAT_004d5b1b = local_e;
      DAT_004d5b1a = local_e;
      iVar1 = 0;
      puVar5 = &DAT_004d5b1d;
      puVar2 = local_b;
      do {
        *puVar5 = *puVar2;
        iVar1 = iVar1 + 1;
        puVar5 = puVar5 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < 7);
      iVar1 = FUN_00466ddc();
      if (iVar1 == 0) {
        DAT_004d59a8 = 0;
        return 0x35;
      }
      return 0x40;
    }
    iVar1 = 0xc;
    DAT_004d512c = local_1c;
  }
  if (iVar1 == 0xc) {
    if (DAT_004d512c < 4) {
      DAT_004d5b1a = (&DAT_004d5144)[DAT_004d512c * 2];
      DAT_004d5b1b = DAT_004d5b1a;
      uVar3 = FUN_0046ca40();
      DAT_004d5b1c = (char)((ulonglong)uVar3 % 6);
      uVar3 = FUN_0046ca40();
      if ((uVar3 % 5 == 0) && (DAT_004d512c == 3)) {
        DAT_004d512c = 4;
      }
      iVar1 = 0;
      puVar2 = &DAT_004d5b1d;
      puVar6 = &DAT_004d514c + DAT_004d512c * 0xc;
      do {
        *puVar2 = *puVar6;
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 2;
      } while (iVar1 < 6);
      DAT_004d5b20._3_1_ = (char)DAT_004d512c * '\x02' + '\f';
      if (DAT_004d512c == 4) {
        DAT_004d512c = 3;
      }
      if (DAT_004d5b1c == '\0') {
        uVar3 = FUN_0046ca40();
        if (uVar3 % 3 != 0) {
          DAT_004d5b1d = DAT_004d5b1d + '\n';
          iVar1 = 1;
          pcVar7 = &DAT_004d5b1e;
          do {
            *pcVar7 = *pcVar7 + -2;
            iVar1 = iVar1 + 1;
            pcVar7 = pcVar7 + 1;
          } while (iVar1 < 6);
        }
      }
      else if (DAT_004d5b1c == '\x01') {
        uVar3 = FUN_0046ca40();
        if (uVar3 % 3 != 0) {
          DAT_004d5b1d = DAT_004d5b1d + -5;
          DAT_004d5b1e = DAT_004d5b1e + -7;
          DAT_004d5b1f = DAT_004d5b1f + '\n';
          DAT_004d5b20._0_1_ = (char)DAT_004d5b20 + '\x05';
          DAT_004d5b20._1_1_ = DAT_004d5b20._1_1_ + -1;
          DAT_004d5b20._2_1_ = DAT_004d5b20._2_1_ + -2;
        }
      }
      else if ((DAT_004d5b1c == '\x04') && (uVar3 = FUN_0046ca40(), uVar3 % 3 != 0)) {
        DAT_004d5b1d = DAT_004d5b1d + -10;
        iVar1 = 1;
        pcVar7 = &DAT_004d5b1e;
        do {
          *pcVar7 = *pcVar7 + '\x02';
          iVar1 = iVar1 + 1;
          pcVar7 = pcVar7 + 1;
        } while (iVar1 < 6);
      }
      iVar1 = FUN_00466ddc();
      if (iVar1 == 0) {
        if (DAT_004d59a8 != 0) {
          DAT_004d59a8 = 0;
          return 0x35;
        }
        return 0x3d;
      }
    }
    else if (DAT_004d512c == 4) {
      return 0x3e;
    }
    uVar4 = 0x43;
    if (DAT_004d5a50 != 0) {
      uVar4 = 0x40;
    }
  }
  else {
    uVar4 = 0x3c;
  }
  return uVar4;
}

