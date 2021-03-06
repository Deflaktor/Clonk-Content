#strict
#include PTGT

Initialize:
  return(1);

Check:
if(ContentsCount(LGP2)<5)
CreateContents(LGP2);
if(ContentsCount(RAP1)<5)
CreateContents(RAP1);
if(ContentsCount(_HLA)<5)
CreateContents(_HLA);
if(ContentsCount(SWMP)<5)
CreateContents(SWMP);
if(ContentsCount(RAP2)<5)
CreateContents(RAP2);
if(ContentsCount(_ARP)<5)
CreateContents(_ARP);
if(ContentsCount(_SR4)<5)
CreateContents(_SR4);
if(ContentsCount(_SLA)<5)
CreateContents(_SLA);
if(ContentsCount(_AP9)<5)
CreateContents(_AP9);
if(ContentsCount(_CGP)<5)
CreateContents(_CGP);
if(ContentsCount(_AP5)<5)
CreateContents(_AP5);
if(ContentsCount(_AP0)<5)
CreateContents(_AP0);
if(ContentsCount(_LGP)<5)
CreateContents(_LGP);
if(ContentsCount(_FMP)<5)
CreateContents(_FMP);
if(ContentsCount(_EMP)<5)
CreateContents(_EMP);
if(ContentsCount(_AP8)<5)
CreateContents(_AP8);
if(ContentsCount(_AP2)<5)
CreateContents(_AP2);
if(ContentsCount(_RP2)<5)
CreateContents(_RP2);
if(ContentsCount(_SR2)<5)
CreateContents(_SR2);
if(ContentsCount(_AP7)<5)
CreateContents(_AP7);
if(ContentsCount(_AP3)<5)
CreateContents(_AP3);
if(ContentsCount(_CEL)<5)
CreateContents(_CEL);
if(ContentsCount(_PP6)<5)
CreateContents(_PP6);
if(ContentsCount(_AP8)<5)
CreateContents(_AP8);
if(ContentsCount(_HMP)<5)
CreateContents(_HMP);
return(1);

Hit:
  Sound("HeavyMetalHit");
  return(1);