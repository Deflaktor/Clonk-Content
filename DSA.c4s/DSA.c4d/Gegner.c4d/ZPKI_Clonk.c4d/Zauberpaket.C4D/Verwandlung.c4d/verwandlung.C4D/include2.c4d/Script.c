#strict
Activate:
if(!Par(1))
{
SetLocal(0,Par());
SetLocal(1,GetID(Par()));
ObjectCall(this(),"ChangeTo");
}
SetLocal(0,Par(1));
SetLocal(1,GetID(Par(1)));
ObjectCall(this(),"ChangeTo");
return(1);


Finish:
ObjectCall(Local(),"UserID",Local(1));
while(Var()<25)
{
if(Not(Random(4)))
  Smoke();
SetVar(0,Var()+1);
}
RemoveObject();
return(1);