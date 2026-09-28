// FUN_004893b4 @ 004893b4 size=41 sig=undefined FUN_004893b4() cc=unknown
// callers: FUN_00438b9c,FUN_00438fe0,FUN_004397a0
// callees: FUN_0048f758,FUN_004a6964,FUN_00489320

void FUN_004893b4(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  uVar1 = FUN_00489320(param_1);
  FUN_004a6964(param_2,uVar1);
  puVar2 = (undefined1 *)FUN_0048f758(param_2,0x2e);
  *puVar2 = 0;
  return;
}

