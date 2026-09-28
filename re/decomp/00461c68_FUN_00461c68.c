// FUN_00461c68 @ 00461c68 size=279 sig=undefined FUN_00461c68() cc=unknown
// callers: FUN_004634a0,FUN_00468ea4,FUN_004684d0,FUN_0043a1f8
// callees: FUN_00460e54,CreateFileA,wsprintfA,FUN_0042836c,FUN_004601f0,FUN_0045f608,CloseHandle,FUN_0045fa34
// strings: \"Could not open file %s.\"|\"Load Game Error\"|\"%s is a savefile from a newer version of deadlock. Unable to load game.\"|\"%s is not a valid saved game.  Unable to load game.\"|\"%s is corrupt.  Unable to load game.\"

undefined4 FUN_00461c68(LPCSTR param_1)

{
  HANDLE hObject;
  int iVar1;
  CHAR local_54 [80];
  
  hObject = CreateFileA(param_1,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000000,(HANDLE)0x0);
  if (hObject == (HANDLE)0xffffffff) {
    wsprintfA(local_54,PTR_s_Could_not_open_file__s__00509a04,param_1);
    FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_54,4,0,0);
  }
  else {
    iVar1 = FUN_0045f608(hObject);
    if (iVar1 == 0) {
      iVar1 = FUN_0045fa34(hObject);
      if (((iVar1 != 0) && (iVar1 = FUN_00460e54(hObject), iVar1 != 0)) &&
         (iVar1 = FUN_004601f0(hObject), iVar1 != 0)) {
        CloseHandle(hObject);
        return 1;
      }
      wsprintfA(local_54,PTR_s__s_is_corrupt__Unable_to_load_ga_00509a14,param_1);
      FUN_0042836c(PTR_s_Load_Game_Error_00509a18,local_54,4,0,0);
      CloseHandle(hObject);
    }
    else {
      if (iVar1 == 1) {
        wsprintfA(local_54,PTR_s__s_is_a_savefile_from_a_newer_ve_00509a20,param_1);
      }
      else {
        wsprintfA(local_54,PTR_s__s_is_not_a_valid_saved_game__Un_00509a0c,param_1);
      }
      FUN_0042836c(PTR_s_Load_Game_Error_00509a10,local_54,4,0,0);
      CloseHandle(hObject);
    }
  }
  return 0;
}

