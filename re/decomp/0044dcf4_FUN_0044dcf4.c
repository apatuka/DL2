// FUN_0044dcf4 @ 0044dcf4 size=255 sig=undefined FUN_0044dcf4() cc=unknown
// callers: FUN_00477838,FUN_00477888,SyncCreateBuilding
// callees: FUN_0044cbec,FindConstructionSite,FUN_0044d7b4,FUN_0047dfdc,FUN_0044d890,FUN_0044c9a0

undefined2 *
FUN_0044dcf4(undefined4 param_1,int param_2,undefined2 param_3,undefined2 param_4,short param_5)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  if (param_5 == -1) {
    param_5 = FindConstructionSite(param_1,param_2);
  }
  if ((param_5 == -1) || (puVar1 = (undefined2 *)FUN_0044cbec(), puVar1 == (undefined2 *)0x0)) {
    puVar1 = (undefined2 *)0x0;
  }
  else {
    FUN_0044d890(param_1,puVar1,param_2,(int)param_5,0);
    *puVar1 = param_3;
    puVar1[1] = puVar1[1] | 2;
    FUN_0044d7b4(param_1,puVar1,(int)param_5,(int)(char)(&DAT_004f9dc5)[param_2 * 0x32]);
    FUN_0044c9a0(param_1,0xffffffff,puVar1,0,0);
    FUN_0047dfdc(param_1);
    if (*(char *)(puVar1 + 2) == '&') {
      puVar2 = (undefined2 *)FUN_0044cbec();
      if (puVar2 != (undefined2 *)0x0) {
        FUN_0044d890(param_1,puVar2,0x27,(int)(short)(param_5 + -10),0);
        *puVar2 = param_4;
        puVar2[1] = puVar2[1] | 2;
        FUN_0044d7b4(param_1,puVar2,(int)(short)(param_5 + -10),(int)DAT_004fa563);
        FUN_0044c9a0(param_1,0xffffffff,puVar2,0,0);
        FUN_0047dfdc(param_1);
      }
    }
  }
  return puVar1;
}

