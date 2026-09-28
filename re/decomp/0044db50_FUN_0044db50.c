// FUN_0044db50 @ 0044db50 size=374 sig=undefined FUN_0044db50() cc=unknown
// callers: NetStartConstruction,FUN_0047597c
// callees: FUN_0044cc40,FUN_004722e0,FUN_00423690,FUN_0044cbec,FUN_0044d7b4,FUN_00471d34,FUN_0044d600,FUN_0044da3c,DebugMessage,FUN_0047dfdc,FUN_0044de9c,FUN_0044d890,FUN_0044c9a0
// strings: \"No Free Buildings!\"

undefined2 * FUN_0044db50(int param_1,int param_2,undefined4 param_3,undefined2 param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 local_40 [13];
  int local_c;
  undefined1 *local_8;
  
  local_8 = &DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8;
  iVar2 = FUN_0044d600(param_1,param_2,param_3);
  if (iVar2 == 0) {
    puVar3 = (undefined2 *)FUN_0044cbec();
    if (puVar3 == (undefined2 *)0x0) {
      DebugMessage(s_No_Free_Buildings__004c6114);
    }
    else {
      FUN_0044de9c(local_8,param_2,(int)*(char *)(param_1 + 0x21),local_40);
      FUN_0044d890(param_1,puVar3,param_2,param_3,local_40[0]);
      local_c = FUN_004722e0(local_8,param_1,local_40,puVar3 + 0x1f);
      if (local_c == 0) {
        *puVar3 = param_4;
        puVar3[1] = puVar3[1] | 2;
        FUN_00423690((int)*(char *)(param_1 + 0x20),0x40,
                     *(undefined4 *)(&DAT_004f9dbc + *(char *)(puVar3 + 2) * 0x32),param_1,0,0);
        FUN_0044d7b4(param_1,puVar3,param_3,(int)(char)(&DAT_004f9dc5)[param_2 * 0x32]);
        if ((char)(&DAT_0059f161)[*(char *)(param_1 + 0x20) * 0x2d8] < '\x03') {
          FUN_0044c9a0(param_1,0xffffffff,puVar3,0,0);
        }
        FUN_0047dfdc(param_1);
        if (*(char *)((int)puVar3 + 5) == '\a') {
          uVar1 = FUN_0044da3c(param_1);
          *(undefined2 *)(param_1 + 0x9b0) = uVar1;
        }
      }
      else {
        FUN_0044cc40(puVar3);
        puVar3 = (undefined2 *)0x0;
        if (*(char *)(param_1 + 0x20) == DAT_0058f1f4) {
          FUN_00471d34(*(undefined4 *)(&DAT_004f9dbc + param_2 * 0x32),local_c,local_40);
        }
      }
    }
  }
  else {
    puVar3 = (undefined2 *)0x0;
  }
  return puVar3;
}

