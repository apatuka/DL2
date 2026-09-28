// FUN_004237d0 @ 004237d0 size=248 sig=undefined FUN_004237d0() cc=unknown
// callers: FUN_004415d0,FUN_00472974,FUN_0046b1ac,FindArtifact,SeaManipulationEffects,FUN_0047cb74,FUN_00457624,FUN_00441400,FUN_0046c49c,FUN_00486d30,FUN_0044b924,FUN_00485668,ConsumeFood,FUN_00484114,FUN_004526b0,FUN_00486964,CheckDiscovery,FUN_00441700,FUN_0044f3f0,FUN_00471b3c,FUN_0046f26c,FUN_0046bc28,SpyCaught
// callees: FUN_00423690,FUN_0045046c

void FUN_004237d0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,int param_7,undefined4 param_8)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == DAT_0058f1f4) {
    iVar1 = FUN_00423690(param_1,param_2,param_3,param_4,param_5,param_6);
    if (iVar1 != -1) {
      (&DAT_00651cc0)[iVar1 * 5] = param_7;
      (&DAT_00651cc4)[iVar1 * 5] = param_8;
      if (param_2 == 0x7b) {
        uVar2 = FUN_0045046c((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],
                             (int)(char)(&DAT_0059f162)[param_7 * 0x2d8]);
        *(undefined4 *)(&DAT_00651cbc + iVar1 * 0x14) = uVar2;
      }
    }
  }
  else if ((DAT_0058f1f4 == DAT_004d5a58) && (-1 < (char)(&DAT_0059f161)[param_1 * 0x2d8] + -3)) {
    (*(code *)(&PTR_FUN_004b5088)[((char)(&DAT_0059f161)[param_1 * 0x2d8] + -3) * 6])
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}

