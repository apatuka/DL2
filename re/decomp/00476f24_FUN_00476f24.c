// FUN_00476f24 @ 00476f24 size=147 sig=undefined FUN_00476f24() cc=unknown
// callers: FUN_00417d54,FUN_0040f060,FUN_0040bfb4,FUN_0040ef18
// callees: FUN_004779c0,BroadcastText

void FUN_00476f24(undefined2 *param_1,int param_2)

{
  FUN_004779c0((int)*(char *)(param_1 + 4),0x11,*param_1,0,(int)*(char *)(param_1 + 0x12),0,0);
  FUN_004779c0((int)*(char *)(param_1 + 4),0x11,*param_1,1,(int)*(char *)((int)param_1 + 0x25),0,0);
  FUN_004779c0((int)*(char *)(param_1 + 4),0x11,*param_1,2,(int)*(char *)(param_1 + 0x13),0,0);
  FUN_004779c0((int)*(char *)(param_1 + 4),0x11,*param_1,3,(int)(short)param_1[0x1b],0,0);
  if (param_2 != 0) {
    BroadcastText((int)*(char *)(param_1 + 4),0x12,*param_1,(int)param_1 + 0xb);
  }
  return;
}

