#strict

Initialize:
  SetAction("Be");
  return(1);

Erstellen:
if(Not(Equal(Local(1),1)))
return(0);
CreateObject(OZRK, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(OZR2, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MF5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MF5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MF5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MI5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MI5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MI5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MI5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(MI5B, Sum(-80, Random(120)),Sum(-80, Random(120)),-1);
CreateObject(KG54,0,0,-1);
RemoveObject(); 
return(1);
