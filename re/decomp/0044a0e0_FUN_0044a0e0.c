// FUN_0044a0e0 @ 0044a0e0 size=485 sig=undefined FUN_0044a0e0() cc=unknown
// callers: 
// callees: FUN_00481a5c,sprintf,FUN_00449cc4,MapWindowPoints
// strings: \"%s\\nOwned by: Nobody\"|\"%s\\nOwned by: %s\"|\"%s\\nOwned by: Unknown\"

undefined1 * FUN_0044a0e0(LONG *param_1)

{
  int iVar1;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  tagPOINT local_24;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  tagPOINT local_c;
  
  if ((DAT_004d5974 == (HWND)0x0) || ((DAT_004d59b4 != 0 && (DAT_004d59b4 != 1)))) {
    if ((DAT_004d59b4 == 5) || (DAT_004d59b4 == 7)) {
      local_24.x = *param_1;
      local_24.y = param_1[1];
      MapWindowPoints((HWND)0x0,DAT_004d5974,&local_24,1);
      iVar1 = FUN_00449cc4(local_24.x,local_24.y,&local_28,&local_2c);
      if ((iVar1 != 0) && (iVar1 == 1)) {
        FUN_00481a5c(local_28,local_2c,local_30,local_34);
      }
    }
  }
  else {
    local_c.x = *param_1;
    local_c.y = param_1[1];
    MapWindowPoints((HWND)0x0,DAT_004d5974,&local_c,1);
    iVar1 = FUN_00449cc4(local_c.x,local_c.y,&local_10,&local_14);
    if (((iVar1 != 0) && (iVar1 == 1)) &&
       ((FUN_00481a5c(local_10,local_14,&local_18,&local_1c), DAT_004d59b4 == 0 ||
        (DAT_004d59b4 == 1)))) {
      iVar1 = (short)(&DAT_005a0552)[local_1c * 200 + local_18 * 5] * 0xadc;
      if ((char)(&DAT_005a4436)[DAT_0058f1f4 + iVar1] < '\x01') {
        sprintf(&DAT_00592d9c,PTR_s__s_Owned_by__Unknown_00509ca8,
                (&PTR_DAT_00509054)[(char)(&DAT_005a43f1)[iVar1]]);
      }
      else if ((&DAT_005a43f0)[iVar1] == -1) {
        sprintf(&DAT_00592d9c,PTR_s__s_Owned_by__Nobody_00509ca0,
                (&PTR_DAT_00509054)[(char)(&DAT_005a43f1)[iVar1]]);
      }
      else {
        sprintf(&DAT_00592d9c,PTR_s__s_Owned_by___s_00509ca4,
                (&PTR_DAT_00509054)[(char)(&DAT_005a43f1)[iVar1]],
                (&PTR_s_ChCh_t_00509038)
                [(char)(&DAT_0059f162)[(char)(&DAT_005a43f0)[iVar1] * 0x2d8]]);
      }
      return &DAT_00592d9c;
    }
  }
  return (undefined1 *)0x0;
}

