#strict

Initialize:
  return(1);

Sterb:
  SetAction(Par(0));
  SetDir(DIR_Left());
  if(Equal(Random(2),1)) SetDir(DIR_Right());
  return(1);

Skellet2:
if(Equal(Local(1),1)){
ChangeDef(_G02);
SetPositionAt();
CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(0,0,255,100), RGBa(255,255,255,200));}
return(1);

Ork2:
if(Equal(Local(1),1)){
ChangeDef(_G01);
SetPositionAt();
CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(0,0,255,100), RGBa(255,255,255,200));}
return(1);

Schwert2:
if(Equal(Local(1),1)){
ChangeDef(KS3A);
SetPositionAt();
CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(0,0,255,100), RGBa(255,255,255,200));}
return(1);