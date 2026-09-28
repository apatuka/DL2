// FUN_00417434 @ 00417434 size=1660 sig=undefined FUN_00417434() cc=unknown
// callers: FUN_00419710
// callees: FUN_00447190,FUN_00447b9c,FUN_00447b54,FUN_00447b0c,FUN_004ae068,FUN_0046d250,FUN_0049eb44,FUN_00447bc0,FUN_00447b30,FUN_004ae230,lstrcatA,FUN_00447b78,wsprintfA,sprintf
// strings: \"Ultra Slow\"|\" round/sec.\"|\" rounds/sec.\"|\"Does Not Shoot\"|\"%d.3 squares\"|\"%d.6 squares\"|\"%d square\"|\"%d squares\"|\"Does Not Move\"|\"point\"|\"points\"|\"%d %s\"|\"credit\"|\"credits\"|\"Group of Units\"|\"(group)\"

void FUN_00417434(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined *puVar4;
  int local_ec [3];
  CHAR local_e0 [200];
  undefined1 local_18 [16];
  int local_8;
  
  if (DAT_004b76b8 == '\0') {
    if (DAT_004b76bc != 0) {
      sprintf(local_e0,&DAT_004b76c8);
      FUN_0049eb44(DAT_004b76b4,6,1,0xf,0,local_e0);
      sprintf(local_e0,&DAT_004b76c8);
      FUN_0049eb44(DAT_004b76b4,0xf,1,0xf,0,local_e0);
      FUN_0046d250((int)*(short *)(DAT_004b76bc + 0x28),local_18);
      sprintf(local_e0,&DAT_004b76c8);
      FUN_0049eb44(DAT_004b76b4,0x11,1,0xf,0,local_e0);
      sprintf(local_e0,&DAT_004b76c8);
      FUN_0049eb44(DAT_004b76b4,0x13,1,0xf,0,local_e0);
      FUN_00447bc0();
      sprintf(local_e0,&DAT_004b76cb);
      FUN_0049eb44(DAT_004b76b4,0x15,1,0xf,0,local_e0);
      FUN_00447b30();
      sprintf(local_e0,&DAT_004b76cb);
      FUN_0049eb44(DAT_004b76b4,0x17,1,0xf,0,local_e0);
      FUN_00447b0c();
      sprintf(local_e0,&DAT_004b76cb);
      FUN_0049eb44(DAT_004b76b4,0x19,1,0xf,0,local_e0);
      FUN_00447b30();
      sprintf(local_e0);
      FUN_0049eb44(DAT_004b76b4,0x1b,1,0xf,0,local_e0);
      FUN_00447b54();
      sprintf(local_e0,&DAT_004b76c8);
      FUN_0049eb44(DAT_004b76b4,0x1d,1,0xf,0,local_e0);
      iVar2 = FUN_00447b9c();
      local_ec[0] = iVar2 + 1;
      local_ec[1] = 9;
      if (iVar2 + 1 < 10) {
        piVar3 = local_ec;
      }
      else {
        piVar3 = local_ec + 1;
      }
      local_ec[2] = 0;
      if (*piVar3 < 0) {
        piVar3 = local_ec + 2;
      }
      iVar2 = *piVar3;
      sprintf(local_e0,&DAT_004b76c8);
      if (iVar2 == 1) {
        lstrcatA(local_e0,PTR_s_round_sec__00509aac);
      }
      else if (1 < iVar2) {
        lstrcatA(local_e0,PTR_s_rounds_sec__00509ab0);
      }
      FUN_0049eb44(DAT_004b76b4,0x1f,1,0xf,0,local_e0);
      local_8 = FUN_00447b78();
      FUN_004ae230((double)local_8);
      iVar2 = FUN_004ae068();
      if (iVar2 == 0) {
        sprintf(local_e0,&DAT_004b76c8);
      }
      else if (iVar2 % 3 == 1) {
        wsprintfA(local_e0,PTR_s__d_3_squares_00509ab8);
      }
      else if (iVar2 % 3 == 2) {
        wsprintfA(local_e0,PTR_s__d_6_squares_00509abc);
      }
      else if (iVar2 == 3) {
        wsprintfA(local_e0,PTR_s__d_square_00509ac0);
      }
      else {
        wsprintfA(local_e0,PTR_s__d_squares_00509ac4);
      }
      FUN_0049eb44(DAT_004b76b4,0x21,1,0xf,0,local_e0);
      cVar1 = FUN_00447190();
      if (cVar1 == 0) {
        wsprintfA(local_e0,PTR_s_Does_Not_Move_00509ac8);
      }
      else {
        sprintf(local_e0,s__d__s_004b76ce,(int)cVar1);
      }
      FUN_0049eb44(DAT_004b76b4,0x23,1,0xf,0,local_e0);
      iVar2 = (int)(char)(&DAT_004faf8a)[*(char *)(DAT_004b76bc + 6) * 0x24];
      if (iVar2 == 0) {
        wsprintfA(local_e0,PTR_DAT_00509ad4);
      }
      else {
        puVar4 = PTR_s_credits_00509adc;
        if (iVar2 == 1) {
          puVar4 = PTR_s_credit_00509ad8;
        }
        sprintf(local_e0,s__d__s_004b76ce,iVar2,puVar4);
      }
      FUN_0049eb44(DAT_004b76b4,0x25,1,0xf,0,local_e0);
    }
  }
  else {
    sprintf(local_e0,&DAT_004b76c8,PTR_s_Group_of_Units_00509424);
    FUN_0049eb44(DAT_004b76b4,6,1,0xf,0,local_e0);
    sprintf(local_e0,&DAT_004b76c8,PTR_s__group__00509428);
    FUN_0049eb44(DAT_004b76b4,0xf,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x11,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x13,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x15,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x17,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x19,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x1b,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x1d,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x1f,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x21,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x23,1,0xf,0,local_e0);
    FUN_0049eb44(DAT_004b76b4,0x25,1,0xf,0,local_e0);
  }
  return;
}

