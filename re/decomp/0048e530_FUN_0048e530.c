// FUN_0048e530 @ 0048e530 size=199 sig=undefined FUN_0048e530() cc=unknown
// callers: 
// callees: FUN_004a6964,GetModuleFileNameA,strlen,FUN_0048937d,SetCurrentDirectoryA
// strings: \"CYGame\"|\"Cyberlore Game\"

undefined4 FUN_0048e530(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  DWORD DVar2;
  CHAR local_20c [260];
  CHAR local_108 [260];
  
  DAT_0065eb98 = param_1;
  DAT_0065eb9c = param_2;
  if (param_3 == 0) {
LAB_0048e571:
    FUN_004a6964(&DAT_0065e998,s_CYGame_0051c388);
  }
  else {
    iVar1 = strlen(param_3);
    if (iVar1 == 0) goto LAB_0048e571;
    FUN_004a6964(&DAT_0065e998,param_3);
  }
  if (param_4 != 0) {
    iVar1 = strlen(param_4);
    if (iVar1 != 0) {
      FUN_004a6964(&DAT_0065ea98,param_4);
      goto LAB_0048e5b4;
    }
  }
  FUN_004a6964(&DAT_0065ea98,s_Cyberlore_Game_0051c38f);
LAB_0048e5b4:
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_108,0x104);
  if (DVar2 != 0) {
    FUN_0048937d(local_108,local_20c);
    SetCurrentDirectoryA(local_20c);
  }
  return 1;
}

