// fread @ 004aa33c size=67 sig=undefined fread() cc=unknown
// callers: FUN_0041161c,GetHighScores,FUN_0048fd95,FUN_00479700,FUN_00410b10,FUN_00479b6c,FUN_0041244c,HdxArchive_Open
// callees: FUN_004ab648,FUN_004aa20c,FUN_004ab710

/* RTL */

uint fread(undefined4 param_1,uint param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    FUN_004ab648(param_4);
    iVar1 = FUN_004aa20c(param_1,param_2 * param_3,param_4);
    FUN_004ab710(param_4);
    param_2 = (param_2 * param_3 - iVar1) / param_2;
  }
  return param_2;
}

