// FUN_0041b500 @ 0041b500 size=262 sig=undefined FUN_0041b500() cc=unknown
// callers: FUN_0041b71c
// callees: FUN_0046d250,FUN_0044c718,FUN_004a6b48,sprintf
// strings: \"Never\"|\"Finished\"|\"1 turn\"|\"%s turns\"

void FUN_0041b500(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_54 [16];
  undefined1 local_44 [64];
  
  sprintf(local_44,&DAT_004b789a,(&DAT_0053b850)[param_1]);
  if (param_1 == 1) {
    if (DAT_0053b854 == 0) {
      sprintf(local_44,PTR_s_Never_005091e8);
    }
    else {
      if (*(short *)(DAT_0053b850 + 0x14) == 0) {
        iVar1 = FUN_0044c718(DAT_0053b850);
        iVar1 = ((iVar1 - *(short *)(DAT_0053b850 + 0x16)) + DAT_0053b854 + -1) / DAT_0053b854;
      }
      else {
        iVar1 = (*(short *)(DAT_0053b850 + 0x14) + DAT_0053b854 + -1) / DAT_0053b854;
      }
      if (iVar1 == 0) {
        sprintf(local_44,PTR_s_Finished_005091f4);
      }
      else if (iVar1 == 1) {
        sprintf(local_44,PTR_s_1_turn_005091ec);
      }
      else {
        uVar2 = FUN_0046d250(iVar1,local_54);
        sprintf(local_44,PTR_s__s_turns_005091f0,uVar2);
      }
    }
  }
  FUN_004a6b48(param_2,local_44,param_3 + -1);
  *(undefined1 *)(param_2 + -1 + param_3) = 0;
  return;
}

