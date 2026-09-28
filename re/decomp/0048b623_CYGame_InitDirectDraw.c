// CYGame_InitDirectDraw @ 0048b623 size=699 sig=undefined CYGame_InitDirectDraw() cc=unknown
// callers: InitCYGame,CYGame_CreateWindow
// callees: FUN_0048bb80,FUN_00495162,FUN_0048b5ea,DirectDrawCreate,GetWindowRect,FUN_0048afe3,FUN_0048afb8,memset,FUN_0049a9e7,GetSystemMetrics
// strings: \"DirectDraw started:\\r\\n\"|\"Pixel Depth: %d\\r\\n\"|\"Pixel Format: %d\\r\\n\"|\"Pixel masks: %#08x %#08x %#08x %#08x\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DirectDraw init, logs pixel format */

undefined4
CYGame_InitDirectDraw
          (HWND param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  HWND pHVar4;
  tagRECT local_84;
  undefined4 local_74;
  uint local_70;
  undefined4 local_60;
  uint local_c;
  undefined4 local_8;
  
  DAT_0051b834 = param_1;
  iVar1 = DirectDrawCreate(0,&DAT_0051b810,0);
  if (iVar1 == 0) {
    uVar2 = 0x11;
    pHVar4 = param_1;
    if (param_2 == 0) {
      uVar2 = 8;
      pHVar4 = (HWND)0x0;
    }
    iVar1 = (**(code **)(*DAT_0051b810 + 0x50))(DAT_0051b810,pHVar4,uVar2);
    if (iVar1 == 0) {
      if ((param_2 == 0) ||
         (iVar1 = (**(code **)(*DAT_0051b810 + 0x54))(DAT_0051b810,param_3,param_4,param_5),
         iVar1 == 0)) {
        local_74 = 0x6c;
        local_70 = 0x20;
        if (param_2 == 0) {
          local_70 = 0;
        }
        local_70 = local_70 | 1;
        local_c = 0x18;
        if (param_2 == 0) {
          local_c = 0;
        }
        local_c = local_c | 0x200;
        local_60 = 1;
        iVar1 = (**(code **)(*DAT_0051b810 + 0x18))(DAT_0051b810,&local_74,&DAT_0051b814,0);
        if (iVar1 == 0) {
          if (param_2 != 0) {
            local_8 = 4;
            iVar1 = (**(code **)(*DAT_0051b814 + 0x30))(DAT_0051b814,&local_8,&DAT_0051b818);
            if (iVar1 != 0) {
              uVar2 = FUN_0048afb8(param_1);
              return uVar2;
            }
          }
          FUN_0048b5ea();
          if ((DAT_0051dcc4 & 0x10) != 0) {
            FUN_00495162(s_DirectDraw_started__0051bd0a);
            FUN_00495162(s_Pixel_Depth___d_0051bd20,DAT_0065e590);
            uVar2 = 1;
            if (_DAT_0065e5a4 != 2) {
              uVar2 = 2;
            }
            FUN_00495162(s_Pixel_Format___d_0051bd32,uVar2);
            FUN_00495162(s_Pixel_masks____08x___08x___08x___0051bd45,DAT_0065e594,DAT_0065e598,
                         DAT_0065e59c,DAT_0065e5a0);
          }
          DAT_0065e5b0 = param_3;
          DAT_0065e5b4 = param_4;
          memset(&DAT_0065e644,0,0xb0);
          _DAT_0065e684 = DAT_0051b814;
          _DAT_0065e648 = param_3;
          _DAT_0065e64c = param_4;
          _DAT_0065e650 = DAT_0065e590;
          _DAT_0065e680 = 0;
          _DAT_0065e66a = DAT_0065e5a4;
          _DAT_0065e66e = 0;
          _DAT_0065e66c = 6;
          FUN_0048bb80(&DAT_0065e644,0);
          memset(&DAT_0065e6f4,0,0xb0);
          _DAT_0065e734 = DAT_0051b818;
          _DAT_0065e6f8 = param_3;
          _DAT_0065e6fc = param_4;
          _DAT_0065e700 = DAT_0065e590;
          _DAT_0065e730 = 0;
          _DAT_0065e71a = DAT_0065e5a4;
          _DAT_0065e71e = 0;
          _DAT_0065e71c = 2;
          FUN_0048bb80(&DAT_0065e6f4,0);
          GetWindowRect(param_1,&local_84);
          if (param_2 == 0) {
            iVar1 = GetSystemMetrics(4);
            iVar3 = GetSystemMetrics(0x21);
            local_84.top = local_84.top + iVar1 + iVar3;
            iVar1 = GetSystemMetrics(0x20);
            local_84.left = local_84.left + iVar1;
          }
          FUN_0048afe3(param_1,local_84.left,local_84.top);
          FUN_0049a9e7(&DAT_0065e670);
          uVar2 = 1;
        }
        else {
          uVar2 = FUN_0048afb8(param_1);
        }
      }
      else {
        uVar2 = FUN_0048afb8(param_1);
      }
    }
    else {
      uVar2 = FUN_0048afb8(param_1);
    }
  }
  else {
    uVar2 = FUN_0048afb8(param_1);
  }
  return uVar2;
}

