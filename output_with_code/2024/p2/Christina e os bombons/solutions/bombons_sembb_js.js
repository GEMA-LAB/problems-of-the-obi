
function compare3DArray(a, b){
    if(a[0] != b[0]){
        if(a[0] < b[0])
            return true;
        return false;
    }
    if(a[1] != b[1]){
        if(a[1] < b[1])
            return true;
        return false;
    }
    if(a[2] != b[2]){
        if(a[2] < b[2])
            return true;
        return false;
    }
    return false;
}


//https://www.geeksforgeeks.org/min-heap-in-javascript/


class MinHeap {
    constructor() {
        this.heap = [];
    }
 
    // Helper Methods
    getLeftChildIndex(parentIndex) {
        return 2 * parentIndex + 1;
    }
    getRightChildIndex(parentIndex) {
        return 2 * parentIndex + 2;
    }
    getParentIndex(childIndex) {
        return Math.floor((childIndex - 1) / 2);
    }
    hasLeftChild(index) {
        return this.getLeftChildIndex(index) < this.heap.length;
    }
    hasRightChild(index) {
        return this.getRightChildIndex(index) < this.heap.length;
    }
    hasParent(index) {
        return this.getParentIndex(index) >= 0;
    }
    leftChild(index) {
        return this.heap[this.getLeftChildIndex(index)];
    }
    rightChild(index) {
        return this.heap[this.getRightChildIndex(index)];
    }
    parent(index) {
        return this.heap[this.getParentIndex(index)];
    }
 
    // Functions to create Min Heap
     
    swap(indexOne, indexTwo) {
        const temp = this.heap[indexOne];
        this.heap[indexOne] = this.heap[indexTwo];
        this.heap[indexTwo] = temp;
    }
 
    peek() {
        if (this.heap.length === 0) {
            return null;
        }
        return this.heap[0];
    }
     
    // Removing an element will remove the
    // top element with highest priority then
    // heapifyDown will be called 
    remove() {
        if (this.heap.length === 0) {
            return null;
        }
        const item = this.heap[0];
        this.heap[0] = this.heap[this.heap.length - 1];
        this.heap.pop();
        this.heapifyDown();
        return item;
    }
 
    add(item) {
        this.heap.push(item);
        this.heapifyUp();
    }
 
    heapifyUp() {
        let index = this.heap.length - 1;
        while (this.hasParent(index) && this.parent(index) > this.heap[index]) {
            this.swap(this.getParentIndex(index), index);
            index = this.getParentIndex(index);
        }
    }
 
    heapifyDown() {
        let index = 0;
        while (this.hasLeftChild(index)) {
            let smallerChildIndex = this.getLeftChildIndex(index);
            if (this.hasRightChild(index) && this.rightChild(index) < this.leftChild(index)) {
                smallerChildIndex = this.getRightChildIndex(index);
            }
            if (compare3DArray(this.heap[index] , this.heap[smallerChildIndex])) {
                break;
            } else {
                this.swap(index, smallerChildIndex);
            }
            index = smallerChildIndex;
        }
    }
     
    printHeap() {
        var heap =` ${this.heap[0]} `
        for(var i = 1; i<this.heap.length;i++) {
            heap += ` ${this.heap[i]} `;
        }
        console.log(heap);
    }
}


var n, m, t;
scanf("%d", "n");
scanf("%d", "m");
scanf("%d", "t");
p = new Array(n);
for(var i = 0; i < n; i++){
    p[i] = new Array(m);
}
for(var i=0;i<n;i++){
    for(var j=0;j<m;j++){
        scanf("%d", "p[i][j]");
    }
}
var x1, y1, x2, y2;
scanf("%d", "x1");
scanf("%d", "y1");
scanf("%d", "x2");
scanf("%d", "y2");
x1--, y1--, x2--, y2--;
var dx = [0, 1, 0, -1];
var dy = [1, 0, -1, 0];
var inf = 1e18;

var dist = new Array(n);
for(var i = 0; i < n; i++){
    dist[i] = new Array(m);
    for(var j =0; j < m; j++){
        dist[i][j] = inf;
    }
}

const pq = new MinHeap();
dist[x1][y1] = 0;
pq.add([0, x1, y1]);
while(true){
    var topo = pq.remove();
    if(topo == null)
        break;
    var d, x, y;
    [d,x,y] = topo;
    if(dist[x][y] < d || p[x][y] == -1) continue;
    for(var k=0;k<4;k++){
        var nx = x + dx[k];
        var ny = y + dy[k];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        var nd = d + p[x][y];
        if(nd < dist[nx][ny]){
            dist[nx][ny] = nd;
            pq.add([nd, nx, ny]);
        }
    }
}


printf("%d\n", Math.floor(t / dist[x2][y2]));
