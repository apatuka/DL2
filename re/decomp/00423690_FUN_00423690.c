// FUN_00423690 @ 00423690 size=318 sig=undefined FUN_00423690() cc=unknown
// callers: FUN_0046b3dc,FUN_0047cdd8,FUN_0047ce94,FUN_0047cf9c,FUN_0047cb74,NoBonus,FUN_0046c49c,FUN_00486d30,FUN_00485668,FUN_0047d288,FUN_004474b0,FUN_0047c730,FUN_004526b0,CheckDiscovery,FUN_004237d0,FUN_0045727c,FUN_0046f26c,FUN_00486e34,ProduceUnits,FindTresure,FUN_004851ec,FUN_00483bd4,FUN_0046b818,FUN_004566c4,FUN_004732a8,FUN_0044b924,FUN_004471c0,ConsumeFood,FUN_0047d49c,DoRiot,FUN_0044db50,FUN_0047d2f0,FUN_0044f3f0,FUN_0047d1e0,FUN_0047d35c
// callees: sprintf,FUN_004234d4,FUN_0042278c,strlen,FUN_004233e0

undefined4
FUN_00423690(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_404 [1024];
  
  if (param_1 == DAT_0058f1f4) {
    iVar1 = FUN_0042278c(param_2);
    if ((0x31 < DAT_0065209c) &&
       (iVar2 = FUN_004233e0((int)*(short *)(&DAT_004fc90c + iVar1 * 0x12)), iVar2 == 0)) {
      return 0xffffffff;
    }
    if (param_2 == 0x3a) {
      sprintf(local_404,*(undefined4 *)((int)&PTR_s_No_event__004fc91a + iVar1 * 0x12),
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]],
              (&PTR_DAT_00508fb8)[param_4],param_5,param_6);
    }
    else {
      sprintf(local_404,*(undefined4 *)((int)&PTR_s_No_event__004fc91a + iVar1 * 0x12),param_3,
              param_4,param_5,param_6);
    }
    uVar3 = strlen(local_404);
    uVar3 = FUN_004234d4(local_404,param_2,uVar3);
  }
  else {
    if ((DAT_0058f1f4 == DAT_004d5a58) && (-1 < (char)(&DAT_0059f161)[param_1 * 0x2d8] + -3)) {
      (*(code *)(&PTR_FUN_004b5088)[((char)(&DAT_0059f161)[param_1 * 0x2d8] + -3) * 6])
                (param_1,param_2,param_3,param_4,param_5,param_6,0,0);
    }
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

