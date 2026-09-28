// FUN_00432824 @ 00432824 size=684 sig=undefined FUN_00432824() cc=unknown
// callers: 
// callees: FUN_0049a8ed,FUN_00481a5c,FUN_0046a588,FUN_004419c8,FUN_004326b0,FUN_004418ec,FUN_004a43da,FUN_0049ea99,FUN_0049f22b,FUN_00463d00,FUN_0049aa64,FUN_00481da0,FUN_0049a93f,BlitSprite8,FUN_0045dfb0
// strings: \"Skirneen Info Ter\"

undefined4 FUN_00432824(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_34 [16];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_2 == 6) {
    iVar1 = FUN_0049ea99(param_1);
    DAT_004c5478 = *(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc);
    DAT_004c547c = *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10);
    DAT_004c5480 = *(undefined4 *)(param_1 + 0x18);
    DAT_004c5484 = *(int *)(param_1 + 0x14);
    DAT_004c5470 = 1;
    DAT_004c5450 = 0;
    local_18 = DAT_004c5484 / (int)DAT_004d5b1b;
    local_1c = *(int *)(param_1 + 0x18) / (int)DAT_004d5b1a;
    if (local_1c < DAT_004c5484 / (int)DAT_004d5b1b) {
      piVar2 = &local_1c;
    }
    else {
      piVar2 = &local_18;
    }
    local_10 = *piVar2;
    local_14 = *(int *)(param_1 + 0x18) - DAT_004d5b1a * local_10;
    iVar1 = FUN_004418ec(s_Skirneen_Info_Ter_004c45b5,
                         *(int *)(param_1 + 0x18) * *(int *)(param_1 + 0x14));
    *(int *)(param_1 + 0x68) = iVar1;
    if (iVar1 != 0) {
      FUN_0046a588(*(undefined4 *)(param_1 + 0x68),local_10,*(undefined4 *)(param_1 + 0x18),local_14
                  );
    }
  }
  else {
    if (param_2 == 3) {
      FUN_0049a8ed();
      iVar1 = FUN_0049ea99(param_1);
      puVar4 = local_34;
      uVar3 = FUN_0049ea99(param_1);
      FUN_0049f22b(uVar3,puVar4);
      FUN_0049aa64(local_34);
      local_20 = *(int *)(param_1 + 0x14) / (int)DAT_004d5b1b;
      local_24 = *(int *)(param_1 + 0x18) / (int)DAT_004d5b1a;
      if (local_24 < local_20) {
        piVar2 = &local_24;
      }
      else {
        piVar2 = &local_20;
      }
      local_10 = *piVar2;
      local_14 = *(int *)(param_1 + 0x18) - DAT_004d5b1a * local_10;
      FUN_00463d00(*(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc),
                   *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10),*(int *)(param_1 + 0x18),
                   *(undefined4 *)(param_1 + 0x14));
      if (*(int *)(param_1 + 0x68) != 0) {
        BlitSprite8(*(undefined4 *)(param_1 + 0x68),*(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc),
                    *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x18)
                    ,*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),1);
      }
      FUN_00481da0(*(int *)(iVar1 + 8) + *(int *)(param_1 + 0xc),
                   *(int *)(iVar1 + 0xc) + *(int *)(param_1 + 0x10),local_10,local_14,3,0);
      FUN_0049a93f();
      return 1;
    }
    if (param_2 == 0x2f) {
      FUN_00481a5c(*(undefined4 *)(param_4 + 0xc),*(undefined4 *)(param_4 + 0x10),&local_8,&local_c)
      ;
      if ((*(byte *)(&DAT_005a43ec + (short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0x2b7) &
          4) == 0) {
        DAT_00558cc0 = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
        FUN_004326b0();
        FUN_0045dfb0(2);
        (&DAT_005a43ec)[DAT_00558cc0 * 0x2b7] = (&DAT_005a43ec)[DAT_00558cc0 * 0x2b7] | 2;
      }
    }
    else if ((param_2 == 2) && (*(int *)(param_1 + 0x68) != 0)) {
      FUN_004419c8(*(undefined4 *)(param_1 + 0x68));
      *(undefined4 *)(param_1 + 0x68) = 0;
    }
  }
  uVar3 = FUN_004a43da(param_1,param_2,param_3,param_4);
  return uVar3;
}

