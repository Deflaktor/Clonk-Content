/*-- Schrein --*/

#strict

protected Initialize:
SetAction("Wait1");
  return(1);

Aktiviert:
CastObjects(_G02,10,1000);
SetAction("Destruct");
return(1);

protected ControlUp:
if(FindObject(_G02,-250,-100,500,100))return(0);
SetAction("Destruct");
Sound("Boom.wav");
return(1);

Zerstoert:
RemoveObject();
return(1);
