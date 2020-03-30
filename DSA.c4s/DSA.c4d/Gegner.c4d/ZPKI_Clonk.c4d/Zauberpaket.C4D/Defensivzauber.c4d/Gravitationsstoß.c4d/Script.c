//vom major}

#strict

local HZBg;

public Activate:
 Sound("Magic1");
 SetAction("wait");
if(ObjectCount(GetID())>1)
	return(RemoveObject());

HZBg=GetGravity();
SetGravity(300); 
var i;
var lw,lh;
lw=LandscapeWidth();
lh=LandscapeHeight();

//Effekte ^_^

for(i=0;i<(lw+lh)/2;i++)
 CreateParticle("MSpark", Random(lw)-GetX(), Random(lh)-GetY(),0,40, 30+Random(50),RGBa(255-Random(50),100-Random(50), 0,128));


return(1);


rem:
SetGravity(HZBg);
RemoveObject();
return(1);   