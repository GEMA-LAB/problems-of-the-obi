program macaco;

var
   teste, N, retangulo		      : Integer;
   AreaEsq, AreaSup, AreaDir, AreaInf : Integer;
   RectEsq, RectSup, RectDir, RectInf : Integer;
   Area_NaoVazia		      : Boolean;

function Max(a, b : Integer):Integer;
begin
   if a>=b then Max:=a
   else Max:=b
end; { Max }

function Min(a, b : Integer):Integer;
begin
   if a<=b then Min:=a
   else Min:=b
end; { Min }

begin
   teste:=1; Area_NaoVazia:=true;
   Readln(N);
   while N > 0 do begin

      Readln(AreaEsq, AreaSup, AreaDir, AreaInf);
      for retangulo:=2 to N do begin
	 Readln(RectEsq, RectSup, RectDir, RectInf);
	 AreaEsq:=Max(AreaEsq, RectEsq);
	 AreaSup:=Min(AreaSup, RectSup);
	 AreaDir:=Min(AreaDir, RectDir);
	 AreaInf:=Max(AreaInf, RectInf);
      end;

      if (AreaEsq >= AreaDir) or (AreaSup <= AreaInf) then
	 Area_NaoVazia:=false;

      Writeln('Teste ', teste);
      if Area_NaoVazia then
	 Writeln(AreaEsq,' ', AreaSup,' ', AreaDir,' ', AreaInf)
      else
	 Writeln('nenhum');
      Writeln;

      Inc(teste); Area_NaoVazia:=true;
      Readln(N);
   end;
end.

