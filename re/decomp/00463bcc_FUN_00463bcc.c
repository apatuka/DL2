// FUN_00463bcc @ 00463bcc size=306 sig=undefined FUN_00463bcc() cc=unknown
// callers: FUN_00464b90,FUN_004442dc
// callees: FUN_00463aec,FUN_0048d391,FUN_0048c2c5,FUN_0048d8a1,FUN_0048c28d,FUN_00463a9c

undefined4 FUN_00463bcc(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(&DAT_0058de34 + param_1 * 0x1c) != 0) {
    FUN_00463aec(param_1);
  }
  *(int *)(&DAT_0058de34 + param_1 * 0x1c) = param_4;
  *(uint *)(&DAT_0058de30 + param_1 * 0x1c) = (uint)(param_4 != 0);
  if (*(int *)(&DAT_0058de34 + param_1 * 0x1c) == 0) {
    iVar1 = FUN_0048c28d(param_2 + 3U & 0xfffc,param_3,0);
    *(int *)(&DAT_0058de34 + param_1 * 0x1c) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  FUN_0048c2c5(*(undefined4 *)(&DAT_0058de34 + param_1 * 0x1c));
  uVar2 = FUN_00463a9c(&DAT_00583e1c + param_1 * 0x1000,
                       *(undefined4 *)(*(int *)(&DAT_0058de34 + param_1 * 0x1c) + 0x10),
                       *(undefined4 *)(*(int *)(&DAT_0058de34 + param_1 * 0x1c) + 8),0xffffffff);
  *(undefined4 *)(&DAT_0058de24 + param_1 * 0x1c) = uVar2;
  *(undefined4 *)(&DAT_0058de28 + param_1 * 0x1c) =
       *(undefined4 *)(*(int *)(&DAT_0058de34 + param_1 * 0x1c) + 4);
  *(undefined4 *)(&DAT_0058de2c + param_1 * 0x1c) =
       *(undefined4 *)(*(int *)(&DAT_0058de34 + param_1 * 0x1c) + 8);
  *(undefined4 *)(&DAT_0058de1c + param_1 * 0x1c) =
       **(undefined4 **)(&DAT_0058de34 + param_1 * 0x1c);
  *(undefined **)(&DAT_0058de20 + param_1 * 0x1c) = &DAT_00583e1c + param_1 * 0x1000;
  iVar1 = FUN_0048d8a1(DAT_004d2360);
  if (iVar1 != 0) {
    FUN_0048d391(*(undefined4 *)(&DAT_0058de34 + param_1 * 0x1c),iVar1);
  }
  return 1;
}

