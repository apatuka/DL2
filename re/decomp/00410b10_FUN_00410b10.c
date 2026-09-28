// FUN_00410b10 @ 00410b10 size=261 sig=undefined FUN_00410b10() cc=unknown
// callers: 
// callees: fclose,free,malloc,fopen,fread

char * FUN_00410b10(undefined4 param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined4 local_c;
  byte local_6;
  char local_5;
  
  iVar2 = fopen(param_1,&DAT_004b6f8f);
  if (iVar2 == 0) {
    pcVar3 = (char *)0x0;
  }
  else {
    iVar4 = fread(&local_c,4,1,iVar2);
    if (iVar4 == 1) {
      pcVar3 = (char *)malloc(local_c);
      pcVar5 = pcVar3;
      while (iVar4 = fread(&local_5,1,1,iVar2), iVar4 == 1) {
        if (local_5 == -0x56) {
          iVar4 = fread(&local_6,1,1,iVar2);
          if (iVar4 != 1) {
            fclose(iVar2);
            free(pcVar3);
            return (char *)0x0;
          }
          iVar4 = fread(&local_5,1,1,iVar2);
          if (iVar4 != 1) {
            fclose(iVar2);
            free(pcVar3);
            return (char *)0x0;
          }
          bVar1 = 0;
          if (local_6 != 0) {
            do {
              *pcVar5 = local_5;
              pcVar5 = pcVar5 + 1;
              bVar1 = bVar1 + 1;
            } while (bVar1 < local_6);
          }
        }
        else {
          *pcVar5 = local_5;
          pcVar5 = pcVar5 + 1;
        }
      }
      fclose(iVar2);
      *param_2 = local_c;
    }
    else {
      fclose(iVar2);
      pcVar3 = (char *)0x0;
    }
  }
  return pcVar3;
}

