// FUN_00414dd4 @ 00414dd4 size=134 sig=undefined FUN_00414dd4() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_00414b64,FUN_0049eb44,FUN_0049ea99,sprintf

void FUN_00414dd4(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 local_104 [256];
  
  if (param_2 == 8) {
    DAT_0053328c = 0;
  }
  else if (param_2 == 3) {
    FUN_00414b64();
    sprintf(local_104,&DAT_004b7070,
            *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + (char)PTR_DAT_004d5988[0x3e] * 0x32));
    puVar6 = local_104;
    uVar5 = 0;
    uVar4 = 0xf;
    uVar3 = 2;
    uVar2 = param_1;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar1,uVar2,uVar3,uVar4,uVar5,puVar6);
  }
  FUN_004a43da(param_1,param_2,param_3,param_4);
  return;
}

