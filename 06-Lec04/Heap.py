
class PriorityQueue: # min heap
    def __init__(self): 
        self.heap = [None]

    def __len__(self):
        return len(self.heap) - 1

    def append(self,key):
    # 1 min_heapify from bottom to top 
            # self.heap.append(key)
            # i = len(self.heap)-1
            # while(i>0):
            #     self.min_heapify(i)
            #     i = i // 2
    # 1 
    # 2 find the right place in that very branch from the new leaf to top, using swap
            # self.heap.append(key)
            # i = len(self.heap)-1
            # while(i > 1):
            #     parent = i // 2
            #     if(self.heap[parent] > self.heap[i]):
            #         self.heap[parent],self.heap[i] = self.heap[i],self.heap[parent]
            #         i = parent
            #     else:
            #         break
    # 2
    # 3 A better way of doing what 2 does, using drifting
        self.heap.append(key)
        i = len(self.heap)-1
        while(i>1):
            parent = i // 2
            if(self.heap[parent] >= key):
                self.heap[i] = self.heap[parent]
                i = parent
            else:
                break
        self.heap[i]= key
    # 3
    def min(self):
        return self.heap[1]

    def pop(self):
    # 1 swap the root and bottom, delete the previous root, run min_heapify (from top to bottom) to build heap
        self.heap[1],self.heap[len(self.heap)-1] = self.heap[len(self.heap)-1],self.heap[1]
        self.heap.pop(-1)
        self.min_heapify(1) # 
    # 1

    def min_heapify(self,n):
    # recursion 
        # heap = self.heap
        # l = n*2
        # r = n*2+1
        # min = n
        # if l<len(heap) and heap[l] < heap[min]:
        #     min = l
        # if  r<len(heap) and heap[r] < heap[min]:
        #     min = r
        # if (min!=n):
        #     heap[n],heap[min] = heap[min],heap[n]
        #     self.min_heapify(min)   
    # iteration 
        heap = self.heap
        while(n<len(self.heap)-1):
            l = n*2
            r = n*2+1
            min = n
            if l<len(heap) and heap[l] < heap[min]:
                min = l
            if  r<len(heap) and heap[r] < heap[min]:
                min = r
            if(min == n):
                break
            else:
                heap[n],heap[min] = heap[min],heap[n]
                n = min


def main():
    H = PriorityQueue()
    H.append(10)
    H.append(1)
    H.append(5)
    H.append(2)
    H.append(3)
    H.append(4)
    H.append(6)
    H.append(0)
    print("len of H :",len(H))
    print(H.heap)
    H.pop()
    print("len of H :",len(H))
    print(H.heap)
    H.pop()
    print("len of H :",len(H))
    print(H.heap)
    H.pop()
    print("len of H :",len(H))
    print(H.heap)
    


if __name__ == "__main__":
    main()
