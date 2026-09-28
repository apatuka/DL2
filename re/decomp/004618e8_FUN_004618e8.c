// FUN_004618e8 @ 004618e8 size=894 sig=undefined FUN_004618e8() cc=unknown
// callers: FUN_00467fc0,ResetNetGame,FUN_00468030,FUN_0043a1f8
// callees: CreateFileA,FUN_0042e434,FUN_00461418,FUN_004a6a94,FUN_00436098,FUN_0046f5d4,ResetVariables,FUN_0041e674,memset,FUN_0045fa34,PreloadSprite2,FUN_004360ec,FUN_0046e730,FUN_0041e6d4,FUN_0042e4c0,FUN_00460330,FUN_0045ff94,FUN_0041e7ec,FUN_0046ce10,FUN_004601f0,FUN_004501b0,FUN_0042e3e4,FUN_004600d0,FUN_0045f828,FUN_0046338c,FUN_00401830,FUN_0045f608,FUN_0045fecc,FUN_00477394,FUN_0045f148,FUN_00486964,wsprintfA,FUN_0042836c,FUN_00436064,FUN_004606f4,FUN_0046ee88,FUN_004612d4,memcpy,FUN_00460a74,FUN_00461328,FUN_004ae594,FUN_0045efd0,FUN_00461078,CloseHandle,FUN_0045fae4,FUN_0045fd28,FUN_0046147c,FUN_0046a844,FUN_0042f0c4,FUN_004238c8
// strings: \"Could not open file %s.\"|\"Load Game Error\"|\"%s is a savefile from a newer version of deadlock. Unable to load game.\"|\"%s is not a valid saved game.  Unable to load game.\"|\"%s is corrupt.  Unable to load game.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004618e8(LPCSTR param_1,int param_2)

{
  HANDLE hObject;
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_70 [20];
  CHAR local_5c [80];
  int local_c;
  int local_8;
  
  memcpy(local_70,&DAT_004d5b10,0x14);
  local_8 = 0x32;
  hObject = CreateFileA(param_1,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000000,(HANDLE)0x0);
  if (hObject == (HANDLE)0xffffffff) {
    wsprintfA(local_5c,PTR_s_Could_not_open_file__s__00509a04,param_1);
    FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_5c,4,0,0);
  }
  else {
    local_c = FUN_0045f608(hObject);
    if (local_c == 0) {
      ResetVariables(param_2);
      FUN_004238c8();
      FUN_0046ee88();
      iVar1 = FUN_0045f828(hObject,param_2);
      if (((((((iVar1 != 0) && (iVar1 = FUN_0045fa34(hObject), iVar1 != 0)) &&
             (iVar1 = FUN_0045fae4(hObject), iVar1 != 0)) &&
            ((iVar1 = FUN_0045fd28(hObject), iVar1 != 0 &&
             (iVar1 = FUN_0045fecc(hObject), iVar1 != 0)))) &&
           ((iVar1 = FUN_0045ff94(hObject), iVar1 != 0 &&
            ((iVar1 = FUN_004600d0(hObject), iVar1 != 0 &&
             (iVar1 = FUN_004601f0(hObject), iVar1 != 0)))))) &&
          (iVar1 = FUN_00460330(hObject), iVar1 != 0)) &&
         ((((iVar1 = FUN_004606f4(hObject), iVar1 != 0 &&
            (iVar1 = FUN_00460a74(hObject), iVar1 != 0)) &&
           (iVar1 = FUN_00461078(hObject,param_2), iVar1 != 0)) &&
          (((iVar1 = FUN_004612d4(hObject), iVar1 != 0 &&
            (iVar1 = FUN_00461328(hObject), iVar1 != 0)) &&
           (iVar1 = FUN_00461418(hObject), iVar1 != 0)))))) {
        CloseHandle(hObject);
        FUN_0046147c();
        iVar1 = FUN_004a6a94(&DAT_004d5b10,local_70,0x14);
        if (iVar1 != 0) {
          local_8 = DAT_004d59b4;
          if (DAT_004d59b4 == 0x2a) {
            FUN_004360ec();
          }
          FUN_0046ce10(0);
          PreloadSprite2();
          FUN_0042e434();
          FUN_0042e3e4();
          FUN_0041e6d4();
          FUN_0041e674();
          _DAT_005126c0 = 0;
          FUN_004ae594(DAT_004d5b14);
          FUN_0046a844();
          FUN_0041e7ec();
          FUN_0042e4c0();
          if (DAT_0058f1ec == 0) {
            FUN_0046338c();
            for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
                puVar2 = puVar2 + 0x2b7) {
              puVar2[7] = puVar2[7] & 0xfff0;
            }
            FUN_0046f5d4();
          }
          else {
            memset(&DAT_004d5b10,0,0x14);
          }
        }
        if (DAT_0058f1ec == 0) {
          if (param_2 != 0) {
            iVar1 = 0;
            do {
              FUN_00401830(iVar1);
              iVar1 = iVar1 + 1;
            } while (iVar1 < 7);
          }
          FUN_00486964();
          FUN_0046e730(1);
          DAT_0065e424 = DAT_004d5af0;
          DAT_004d1bf4 = 1;
          DAT_004d59bc = 1;
          FUN_004501b0();
          if (DAT_004d5b2c != 0) {
            FUN_0045efd0(DAT_004d5b30);
          }
          FUN_0045f148();
          if (DAT_0058f1fc == 0) {
            FUN_00477394(DAT_0059f15c);
          }
          if (DAT_004d59b4 == 0x47) {
            FUN_0042e4c0();
          }
          if ((DAT_0059f154 == 1) && (0 < DAT_004d5a94)) {
            FUN_0042f0c4((DAT_004d5a94 + -1) % 6,0);
          }
          return 1;
        }
        if (DAT_004d59b4 == 0x47) {
          FUN_0042e4c0();
        }
        if (local_8 == 0x2a) {
          FUN_00436098();
          FUN_00436064();
        }
        return 0;
      }
      DAT_0058f1ec = 1;
      wsprintfA(local_5c,PTR_s__s_is_corrupt__Unable_to_load_ga_00509a14,param_1);
      FUN_0042836c(PTR_s_Load_Game_Error_00509a18,local_5c,4,0,0);
      CloseHandle(hObject);
    }
    else {
      if (local_c == 1) {
        wsprintfA(local_5c,PTR_s__s_is_a_savefile_from_a_newer_ve_00509a20,param_1);
      }
      else {
        wsprintfA(local_5c,PTR_s__s_is_not_a_valid_saved_game__Un_00509a0c,param_1);
      }
      FUN_0042836c(PTR_s_Load_Game_Error_00509a10,local_5c,4,0,0);
      CloseHandle(hObject);
    }
  }
  return 0;
}

