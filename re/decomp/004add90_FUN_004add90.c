// FUN_004add90 @ 004add90 size=35 sig=undefined FUN_004add90() cc=unknown
// callers: FUN_00473324,FUN_00424f14
// callees: FUN_004addb4

char * FUN_004add90(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  while( true ) {
    cVar1 = FUN_004addb4((int)*pcVar2);
    *pcVar2 = cVar1;
    if (cVar1 == '\0') break;
    pcVar2 = pcVar2 + 1;
  }
  return param_1;
}

