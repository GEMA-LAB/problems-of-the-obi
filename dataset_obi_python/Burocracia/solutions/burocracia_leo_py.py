#!/usr/bin/env python3

class LazySegmentTree:
    def __init__(self, data, default=1000000, func=min):
        """initialize the lazy segment tree with data"""
        self._default = default
        self._func = func

        self._len = len(data)
        self._size = _size = 1 << (self._len - 1).bit_length()
        self._lazy = [default] * (2 * _size)

        self.data = [default] * (2 * _size)
        self.data[_size:_size + self._len] = data
        for i in reversed(range(_size)):
            self.data[i] = func(self.data[i + i], self.data[i + i + 1])

    def __len__(self):
        return self._len

    def _push(self, idx):
        """push query on idx to its children"""
        # Let the children know of the queries
        q, self._lazy[idx] = self._lazy[idx], 1000000

        self._lazy[2 * idx] = self._func(q, self._lazy[2 * idx])
        self._lazy[2 * idx + 1] = self._func(q, self._lazy[2 * idx + 1])
        self.data[2 * idx] = self._func(q, self.data[2 * idx])
        self.data[2 * idx + 1] = self._func(q, self.data[2 * idx + 1])

    def _update(self, idx):
        """updates the node idx to know of all queries applied to it via its ancestors"""
        for i in reversed(range(1, idx.bit_length())):
            self._push(idx >> i)

    def _build(self, idx):
        """make the changes to idx be known to its ancestors"""
        idx >>= 1
        while idx:
            self.data[idx] = self._func(self._func(self.data[2 * idx], self.data[2 * idx + 1]), self._lazy[idx])
            idx >>= 1

    def add(self, start, stop, value):
        """lazily add value to [start, stop)"""
        start = start_copy = start + self._size
        stop = stop_copy = stop + self._size
        while start < stop:
            if start & 1:
                self._lazy[start] = self._func(value,self._lazy[start])
                self.data[start] = self._func(value,self.data[start])
                start += 1
            if stop & 1:
                stop -= 1
                self._lazy[stop] = self._func(value,self._lazy[stop])
                self.data[stop] = self._func(value,self.data[stop])
            start >>= 1
            stop >>= 1

        # Tell all nodes above of the updated area of the updates
        self._build(start_copy)
        self._build(stop_copy - 1)

    def query(self, start, stop, default=1000000):
        """func of data[start, stop)"""
        start += self._size
        stop += self._size

        # Apply all the lazily stored queries
        self._update(start)
        self._update(stop - 1)

        res = default
        while start < stop:
            if start & 1:
                res = self._func(res, self.data[start])
                start += 1
            if stop & 1:
                stop -= 1
                res = self._func(res, self.data[stop])
            start >>= 1
            stop >>= 1
        return res

    def __repr__(self):
        return "LazySegmentTree({0})".format(self.data)


n = int(input())

pai = list(map(int,input().split()))

pai = [0] + pai

for i in range(1, len(pai)):
    pai[i]-=1

g = [[] for i in range(n)]

for i in range(1,n):
    g[pai[i]].append(i)


q = int(input())

height = [0]*n
tin = [0]*n
tout = [0]*n

st = [(0,0)]

timer = -1

while(len(st)):
    v, flag = st.pop()

    if(flag):
        tout[v] = tin[v]
        for u in g[v]:
            tout[v] = max(tout[v], tout[u])
    else:
        timer+=1
        tin[v] = timer

        st.append((v,1))

        for u in g[v]:
            height[u] = height[v]+1
            st.append((u,0))

invtin = [0]*n

for i in range(n):
    invtin[tin[i]] = i

id = [0]*n

for i in range(n):
    id[i] = i

tree = LazySegmentTree(id,n,min)


lift = [[0]*n for i in range(20)]

for i in range(n):
    lift[0][i] = pai[i]

for i in range(1,20):
    for j in range(n):
        lift[i][j] = lift[i-1][lift[i-1][j]]

def k_up(v, k):
    for i in range(20):
        if(k&1):
            v = lift[i][v]
        k>>=1
    return v

for _ in range(q):
    
    l = list(map(int,input().split()))

    t = l[0]
    v = l[1]
    v-=1
    if(t == 1):
        k = l[2]
        # print("->",tin[v],tree.query(tin[v],tin[v]+1,n))
        newv = invtin[tree.query(tin[v],tin[v]+1,n)]
        k-=newv != v
        
        print(k_up(newv,k)+1)

    else:
        tree.add(tin[v], tout[v]+1, tin[v])
