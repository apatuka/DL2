// FUN_00475f80 @ 00475f80 size=260 sig=undefined FUN_00475f80() cc=unknown
// callers: FUN_00420e34,FUN_0041d414,FUN_0041026c
// callees: FUN_00474cc4,FUN_00474d0c,FUN_00477f9c,FUN_0044df94,MessagePump,FUN_004779c0
// strings: \"Broadcast\"

uint FUN_00475f80(int param_1,char *param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_58;
  undefined4 local_52;
  short local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  
  if (DAT_0058f1fc == 0) {
    uVar1 = FUN_0044df94(param_1,param_2,param_3);
  }
  else if (DAT_0058f1f4 == DAT_004d5a58) {
    uVar1 = FUN_0044df94(param_1,param_2,param_3);
    if ((uVar1 & 0xf001) == 0) {
      local_5f = 0xff;
      local_5e = 0xfe;
      local_60 = DAT_004d5a54;
      local_52 = 0x5c;
      local_58 = 0x17;
      local_4a = (short)*param_2;
      local_48 = (undefined2)param_3;
      local_46 = *(undefined2 *)(param_1 + 0x1a);
      local_44 = 0;
      FUN_00474cc4(s_Broadcast_004dbec4,&local_60,0);
    }
  }
  else {
    FUN_004779c0((int)*param_2,0x17,param_3,(int)*(short *)(param_1 + 0x1a),0,0,0);
    iVar2 = FUN_00474d0c(0x17);
    if ((iVar2 == 1) || (iVar2 == 2)) {
      uVar1 = (uint)DAT_0065354e;
    }
    else {
      uVar1 = 0xffffffff;
    }
    if (iVar2 == 2) {
      while ((DAT_00653598 != '\x17' || ((int)DAT_006535a6 != (int)*param_2))) {
        MessagePump();
        FUN_00477f9c();
      }
    }
  }
  return uVar1;
}

