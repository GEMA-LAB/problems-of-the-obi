program fusoes;
var
   pai, rank: array [1..100000] of longint;

function find(u: longint): longint;
begin
   if pai[u] = u then
      find := u
   else begin
      pai[u] := find(pai[u]);
      find := pai[u];
   end;
end;

procedure union(u, v: longint);
begin
   u := find(u);
   v := find(v);
   if rank[u] > rank[v] then
      pai[v] := u
   else if rank[u] < rank[v] then
      pai[u] := v
   else begin
      pai[u] := v;
      rank[v] := rank[v] + 1;
   end;
end;

var
   N, K: longint;
   op: char;
   U, V: longint;
   i: longint;
begin
   readln(N, K);
   for i := 1 to N do begin
      pai[i] := i;
      rank[i] := 0;
   end;
   for i := 1 to K do begin
      readln(op, U, V);
      if op = 'F' then
         union(U, V)
      else
         if find(U) = find(V) then
            writeln('S')
         else
            writeln('N')
   end;
end.
