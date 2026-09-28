// FUN_00429464 @ 00429464 size=548 sig=undefined FUN_00429464() cc=unknown
// callers: 
// callees: FUN_00476c44,FUN_00427ee8,sprintf,FUN_004767f0,FUN_00427f04,FUN_00427e6c,FUN_004503f4,FUN_0042836c,FUN_0044a000,FUN_00425364,FUN_00477f9c,FUN_00427e80,FUN_00476b58
// strings: \"Proposing a %s pact to the %s\"|\"Proposing a pact\"|\"The %s are busy with other matters.  Try them later.\"

void FUN_00429464(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_404 [1024];
  
  if (DAT_004d5aa0 != '\0') {
    FUN_00476b58(DAT_0058f1f4,param_1,param_2);
    return;
  }
  sprintf(local_404,PTR_s_Proposing_a__s_pact_to_the__s_0050939c,(&PTR_DAT_00508fb8)[param_2],
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]]);
  FUN_00427e80(1,PTR_s_Proposing_a_pact_00509398,local_404,0,5);
  FUN_00427f04();
  FUN_0044a000();
  FUN_00476c44(DAT_0058f1f4,param_1,param_2);
  iVar2 = 0;
  while ((*(int *)(&DAT_006534fc + DAT_0058f1f4 * 4) == 2 && (iVar2 == 0))) {
    FUN_00477f9c();
    iVar2 = FUN_00427e6c();
  }
  FUN_00427ee8();
  if (iVar2 == 4) {
    FUN_004767f0(param_1,0);
    return;
  }
  iVar2 = *(int *)(&DAT_006534fc + DAT_0058f1f4 * 4);
  if (iVar2 != 0) {
    if (iVar2 == 1) {
      sprintf(local_404,PTR_s_The__s_are_busy_with_other_matte_005093bc,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]]);
      FUN_0042836c(PTR_s_Proposing_a_pact_00509398,local_404,4,0,5);
      goto LAB_00429672;
    }
    if (iVar2 == 3) {
      uVar3 = 0;
      uVar1 = FUN_004503f4((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],0x12,0xffffffff);
      FUN_00425364(uVar1,uVar3);
      FUN_00476b58(DAT_0058f1f4,param_1,param_2);
      goto LAB_00429672;
    }
    if (iVar2 != 4) goto LAB_00429672;
  }
  if ((*(int *)(&DAT_005220a4 + DAT_0058f1f4 * 4 + param_1 * 0x1c) < 0) ||
     ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03')) {
    uVar3 = 0;
    uVar1 = FUN_004503f4((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],0x11,0xffffffff);
    FUN_00425364(uVar1,uVar3);
  }
  else {
    uVar3 = 0;
    uVar1 = FUN_004503f4((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],0x10,0xffffffff);
    FUN_00425364(uVar1,uVar3);
  }
LAB_00429672:
  FUN_004767f0(DAT_0058f1f4,2);
  return;
}

