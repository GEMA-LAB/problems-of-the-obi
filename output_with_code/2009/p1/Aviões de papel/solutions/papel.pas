{ Solucao para o problema "Avioes de Papel" da OBI 2009
   por: Igor Ribeiro de Assis }

program papel;

var
   C, P, F : longint;

begin 

   readln(C, P, F);
   if C * F <= P then
      writeln('S')
   else
      writeln('N');
   
end.
