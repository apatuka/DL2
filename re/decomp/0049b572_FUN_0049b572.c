// FUN_0049b572 @ 0049b572 size=69 sig=undefined FUN_0049b572() cc=unknown
// callers: FUN_0049b5b7
// callees: 

undefined4 FUN_0049b572(int param_1,int param_2,int param_3,uint *param_4)

{
  ushort *puVar1;
  
  if (param_4 != (uint *)0x0) {
    puVar1 = (ushort *)
             (*(short *)(param_1 + 6) * param_3 + param_1 +
              (((int)*(short *)(param_1 + 8) & 3U) + 1) * param_2 + 0x1a);
    if ((*(byte *)(param_1 + 8) & 3) == 0) {
      *param_4 = (uint)*(byte *)puVar1;
    }
    else {
      *param_4 = (uint)*puVar1;
    }
  }
  return 1;
}

