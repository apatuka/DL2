// FUN_004503f4 @ 004503f4 size=117 sig=undefined FUN_004503f4() cc=unknown
// callers: FUN_00425ac4,FUN_0041edd8,FUN_0042d0ac,FUN_004505d0,FUN_00429464,FUN_0042ee18,FUN_00431128,FUN_00450528,NetBreakPact,FUN_00435ed0,FUN_004234d4,FUN_00422f7c
// callees: FUN_0046ca40

undefined4 FUN_004503f4(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  
  if (param_1 == 7) {
    puVar3 = (&PTR_PTR_004cabc8)[param_2 * 2];
    uVar2 = *(uint *)(&DAT_004cabcc + param_2 * 8);
  }
  else if (param_1 == 8) {
    puVar3 = (&PTR_PTR_004cabe8)[param_2 * 2];
    uVar2 = *(uint *)(&DAT_004cabec + param_2 * 8);
  }
  else {
    uVar2 = *(uint *)(&DAT_004ca3b4 + param_1 * 8 + param_2 * 0x38);
    puVar3 = (&PTR_PTR_004ca3b0)[param_2 * 0xe + param_1 * 2];
  }
  if (param_3 == -1) {
    uVar1 = FUN_0046ca40();
    uVar1 = uVar1 % uVar2;
  }
  else {
    uVar1 = param_3 % (int)uVar2;
  }
  return *(undefined4 *)(puVar3 + uVar1 * 4);
}

