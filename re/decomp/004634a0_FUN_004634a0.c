// FUN_004634a0 @ 004634a0 size=556 sig=undefined FUN_004634a0() cc=unknown
// callers: RaceInit
// callees: FUN_004879b0,FUN_004632f4,FUN_004ae594,FUN_0041e6d4,FUN_0041e8d0,FUN_00462348,FUN_0046338c,FUN_00461c68,FUN_00466128,FUN_00463014,FUN_00462724,FUN_00462994,FUN_0041e7ec,FUN_00466218,FUN_00413930,FUN_0042836c,FUN_004626f0,FUN_0046a844,FUN_004669d8,FUN_0041e674,FUN_004ae5b0,FUN_00442678,FUN_0041e8f8
// strings: \"Launching Colony Ship\"|\"Oops, this world is not usable.  Click OK to try again.\"|\"World Generation Error!\"

void FUN_004634a0(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_c [2];
  
  FUN_0041e6d4();
  FUN_0041e674();
LAB_004634ae:
  do {
    if (DAT_004d5a88 == 0) {
      DAT_004d5b10 = FUN_004ae5b0();
    }
    FUN_004ae594(DAT_004d5b10);
    FUN_0041e8f8(PTR_s_Launching_Colony_Ship_00509988);
    local_c[0] = (int)DAT_004d5b20._3_1_;
    local_c[1] = 0xc;
    piVar2 = local_c;
    if (DAT_004d5b20._3_1_ < 0xc) {
      piVar2 = local_c + 1;
    }
    DAT_004d5b18 = (short)(((int)DAT_004d5b1a * (int)DAT_004d5b1b) / *piVar2);
    if ((int)DAT_004d5b18 < DAT_004d5aec * 2 + 1) {
      DAT_004d5b18 = (short)DAT_004d5aec * 2 + 1;
    }
    if (0x68 < DAT_004d5b18) {
      DAT_004d5b18 = 0x68;
    }
    FUN_004626f0();
    FUN_0041e8d0(10);
    FUN_004879b0();
    for (iVar3 = 1; iVar3 <= DAT_004d5b18; iVar3 = iVar3 + 1) {
      iVar1 = FUN_00462348();
      if (iVar1 != 0) {
        return;
      }
      FUN_00462724(iVar3);
    }
    FUN_0041e8d0(0x19);
    iVar3 = FUN_00462348();
    if (iVar3 != 0) {
      return;
    }
    FUN_004879b0();
    FUN_00462994();
    iVar3 = FUN_00462348();
    if (iVar3 != 0) {
      return;
    }
    FUN_004879b0();
    iVar3 = FUN_00466128();
  } while (iVar3 == 0);
  if (DAT_004d5a88 != 0) {
    FUN_00461c68(&DAT_005597d5);
  }
  FUN_00463014();
  if (DAT_004d5aa0 != '\0') {
    iVar3 = FUN_00413930();
    if (iVar3 == 2) {
      DAT_0058f1ec = 1;
      return;
    }
    if (iVar3 == 999) goto LAB_004634ae;
  }
  FUN_0041e8d0(0x4b);
  iVar3 = FUN_00462348();
  if (iVar3 != 0) {
    return;
  }
  FUN_004879b0();
  FUN_004632f4();
  FUN_0041e8d0(0x5a);
  iVar3 = FUN_00462348();
  if (iVar3 != 0) {
    return;
  }
  FUN_004879b0();
  iVar3 = FUN_00466218();
  if (iVar3 != 0) {
    FUN_0041e8d0(100);
    FUN_004879b0();
    FUN_004ae594(DAT_004d5b14);
    FUN_0046a844();
    iVar3 = FUN_00462348();
    if (iVar3 != 0) {
      FUN_0041e7ec();
      return;
    }
    FUN_004669d8(1);
    FUN_00442678();
    FUN_0046338c();
    FUN_0041e7ec();
    return;
  }
  if ((DAT_004d5aa0 != '\0') &&
     (iVar3 = FUN_0042836c(PTR_s_World_Generation_Error__0050998c,
                           PTR_s_Oops__this_world_is_not_usable__C_00509990,0x18,0,4), iVar3 == 2))
  {
    DAT_0058f1ec = 1;
    return;
  }
  goto LAB_004634ae;
}

