// FUN_004818ac @ 004818ac size=127 sig=undefined FUN_004818ac() cc=unknown
// callers: FUN_0048192c
// callees: BlitSprite8,FUN_00483038,ReadDataFileChunk
// strings: \"SPRITENW.DAT\"

void FUN_004818ac(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined1 local_408 [1024];
  undefined4 local_8;
  
  iVar1 = (int)*(short *)(param_1 + 6);
  param_3 = param_3 - iVar1;
  if (param_3 < 0) {
    iVar1 = iVar1 + param_3;
    param_3 = 0;
  }
  ReadDataFileChunk(s_SPRITENW_DAT_004dce20,local_408,*(undefined4 *)(param_1 + 0xc),
                    (int)*(short *)(param_1 + 4) * (int)*(short *)(param_1 + 6));
  local_8 = *(undefined4 *)(param_1 + 8);
  *(undefined1 **)(param_1 + 8) = local_408;
  FUN_00483038(param_1);
  BlitSprite8(local_408,param_2,param_3,(int)*(short *)(param_1 + 4),iVar1,
              (int)*(short *)(param_1 + 4),0);
  *(undefined4 *)(param_1 + 8) = local_8;
  return;
}

