{ Solucao para o problema "Número de Envelopes" da OBI 2009
   por: Igor Ribeiro de Assis }

program envelopes;

const
   MAXK	= 1010;

var 
   N, K, menor, i, x : longint;
   qtd		     : array[1..MAXK] of longint;

begin

   readln(N, K);

   { conta quantos rótulos de cada tipo Aldo tem }
   for i := 1 to K do qtd[i] := 0;
   for i := 1 to N do begin
      read(x);
      qtd[x] += 1;
   end;

   { o máximo de envelopes é igual ao numero de rótulos em menor quantidade }
   menor := qtd[1];
   for i := 2 to K do
      if qtd[i] < menor then
	 menor := qtd[i];

   writeln(menor);
   
end.
