// FUN_00489c98 @ 00489c98 size=526 sig=undefined FUN_00489c98() cc=unknown
// callers: FUN_0049624e
// callees: FUN_0048bb44,memset,CoCreateInstance,FUN_0048bb6c,FUN_00495162
// strings: \"Initializing Direct Sound:\"|\"\\r\\nWarning: (DirectSound) Primary buffer could not be set to preferred format.\\r\\n\"|\"\\r\\n(DirectSound) Primary buffer successfully set to preferred format.\\r\\n\"|\"Direct Sound: Error starting primary buffer\\r\\n\"|\"SUCCESSFUL\\r\\n\"|\"Direct Sound: Cannot create primary buffer\\r\\n\"|\"Direct Sound: SetCooperativeLevel failed\\r\\n\"|\"Direct Sound:Failed to initialize DirectSound object\\r\\n\"

undefined4 FUN_00489c98(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_90 [20];
  undefined4 local_7c [24];
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_8 [4];
  
  iVar1 = FUN_0048bb44();
  if (iVar1 == 0) {
    if ((DAT_0051dcc4 & 0x10) != 0) {
      FUN_00495162(s__Failed_to_initialize_COM_librar_0051b623 + 1);
    }
    uVar2 = 0;
  }
  else {
    if ((DAT_0051dcc4 & 0x10) != 0) {
      FUN_00495162(s_Initializing_Direct_Sound__0051b647);
    }
    iVar1 = CoCreateInstance((IID *)&DAT_0051b604,(LPUNKNOWN)0x0,1,(IID *)&DAT_0051b614,
                             &DAT_0051b5fc);
    if ((iVar1 < 0) || (DAT_0051b5fc == (int *)0x0)) {
      if ((DAT_0051dcc4 & 0x10) != 0) {
        FUN_00495162(s_Direct_Sound_Failed_to_initializ_0051b78c);
      }
    }
    else {
      iVar1 = (**(code **)(*DAT_0051b5fc + 0x28))(DAT_0051b5fc,0);
      if (iVar1 < 0) {
        if ((DAT_0051dcc4 & 0x10) != 0) {
          FUN_00495162(s_Direct_Sound__SetCooperativeLeve_0051b761);
        }
      }
      else {
        uVar2 = 3;
        if (param_1 == 0) {
          uVar2 = 1;
        }
        iVar1 = (**(code **)(*DAT_0051b5fc + 0x18))(DAT_0051b5fc,DAT_0051b834,uVar2);
        if (iVar1 < 0) {
          if ((DAT_0051dcc4 & 0x10) != 0) {
            FUN_00495162(s_Direct_Sound__Cannot_create_prim_0051b734);
          }
        }
        else {
          memset(&local_1c,0,0x14);
          local_1c = 0x14;
          local_18 = 1;
          iVar1 = (**(code **)(*DAT_0051b5fc + 0xc))(DAT_0051b5fc,&local_1c,&DAT_0051b600,0);
          if (-1 < iVar1) {
            (**(code **)(*DAT_0051b600 + 0x14))(DAT_0051b600,local_90,0x12,local_8);
            local_7c[0] = 0x60;
            (**(code **)(*DAT_0051b5fc + 0x10))(DAT_0051b5fc,local_7c);
            if (param_2 != 0) {
              iVar1 = (**(code **)(*DAT_0051b600 + 0x38))(DAT_0051b600,param_2);
              if (iVar1 < 0) {
                FUN_00495162(s_Warning___DirectSound__Primary_b_0051b662);
              }
              else {
                FUN_00495162(s__DirectSound__Primary_buffer_suc_0051b6b2);
              }
            }
            iVar1 = (**(code **)(*DAT_0051b600 + 0x30))(DAT_0051b600,0,0,1);
            if (iVar1 < 0) {
              if ((DAT_0051dcc4 & 0x10) != 0) {
                FUN_00495162(s_Direct_Sound__Error_starting_pri_0051b6f9);
              }
              (**(code **)(*DAT_0051b600 + 8))(DAT_0051b600);
              DAT_0051b600 = (int *)0x0;
            }
            else if ((DAT_0051dcc4 & 0x10) != 0) {
              FUN_00495162(s_SUCCESSFUL_0051b727);
            }
          }
        }
      }
    }
    if ((iVar1 < 0) && (DAT_0051b5fc != (int *)0x0)) {
      (**(code **)(*DAT_0051b5fc + 8))(DAT_0051b5fc);
      DAT_0051b5fc = (int *)0x0;
    }
    if (iVar1 < 0) {
      FUN_0048bb6c();
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

