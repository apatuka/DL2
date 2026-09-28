// FUN_004415d0 @ 004415d0 size=303 sig=undefined FUN_004415d0() cc=unknown
// callers: FUN_00441700,NetBreakPact
// callees: FUN_004237d0

undefined4 FUN_004415d0(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  char *local_8;
  
  if (DAT_004d5af4 == 0) {
    uVar1 = 0;
  }
  else {
    iVar3 = 0;
    uVar2 = ~param_3;
    (&DAT_0059f3da)[param_1 * 0xb6 + param_2] = (&DAT_0059f3da)[param_1 * 0xb6 + param_2] & uVar2;
    (&DAT_0059f3da)[param_2 * 0xb6 + param_1] = (&DAT_0059f3da)[param_2 * 0xb6 + param_1] & uVar2;
    (&DAT_0059f3f6)[param_1 * 0xb6 + param_2] = (&DAT_0059f3f6)[param_1 * 0xb6 + param_2] & uVar2;
    (&DAT_0059f3f6)[param_2 * 0xb6 + param_1] = (&DAT_0059f3f6)[param_2 * 0xb6 + param_1] & uVar2;
    local_8 = &DAT_0059f161;
    do {
      if ((('\x02' < *local_8) && (param_1 != iVar3)) && (param_2 != iVar3)) {
        FUN_004237d0(iVar3,0x73,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],
                     (int)*(char *)((int)&PTR_DAT_00508fb8 + param_3),
                     (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_2 * 0x2d8]],0,param_1,
                     param_2);
      }
      iVar3 = iVar3 + 1;
      local_8 = local_8 + 0x2d8;
    } while (iVar3 < 7);
    uVar1 = 1;
  }
  return uVar1;
}

