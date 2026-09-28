// FUN_00413980 @ 00413980 size=422 sig=undefined FUN_00413980() cc=unknown
// callers: FUN_00413bc8,FUN_00413b3c,FUN_00413cd0
// callees: FUN_0049eb44,FUN_0044e9e4,sprintf

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00413980(undefined1 param_1)

{
  undefined1 local_84 [128];
  
  switch(param_1) {
  case 0:
    _DAT_0053320c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xc,100,1);
    sprintf(local_84,&DAT_004b7050,_DAT_0053320c);
    FUN_0049eb44(DAT_004b7028,6,1,0xf,0,local_84);
    break;
  case 1:
    _DAT_0053320c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xf,100,1);
    sprintf(local_84,&DAT_004b7050,_DAT_0053320c);
    FUN_0049eb44(DAT_004b7028,8,1,0xf,0,local_84);
    break;
  case 2:
    _DAT_0053320c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,4,100,1);
    sprintf(local_84,&DAT_004b7050,_DAT_0053320c);
    FUN_0049eb44(DAT_004b7028,0xe,1,0xf,0,local_84);
    break;
  case 3:
    _DAT_0053320c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xd,100,1);
    sprintf(local_84,&DAT_004b7050,_DAT_0053320c);
    FUN_0049eb44(DAT_004b7028,10,1,0xf,0,local_84);
    break;
  case 4:
    _DAT_0053320c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,3,100,1);
    sprintf(local_84,&DAT_004b7050,_DAT_0053320c);
    FUN_0049eb44(DAT_004b7028,0xc,1,0xf,0,local_84);
  }
  return;
}

