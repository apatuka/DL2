// FUN_0041e1fc @ 0041e1fc size=112 sig=undefined FUN_0041e1fc() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_004590f0

void FUN_0041e1fc(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  
  puVar1 = (&PTR_DAT_004d078c)
           [(char)(&DAT_0059f162)
                  [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8] * 3];
  FUN_004590f0(DAT_004d5974,*(undefined4 *)(puVar1 + 8),param_1,param_2,(int)*(short *)(puVar1 + 4),
               (int)*(short *)(puVar1 + 6),0,FUN_0041db10);
  return;
}

