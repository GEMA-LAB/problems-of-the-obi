{ OBI2005              }
{ Tarefa Frota de Táxi }
{ r. anido             }

program taxi;

var a, g, ra, rg :  real;

begin
	readln(a, g, ra, rg);
	if (a/ra < g/rg) then
		writeln('A')
	else
		writeln('G');
end.
