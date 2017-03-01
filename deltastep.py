INT_MAX = 2147483647

def parse_input():
    line = raw_input().split()
    size = int(line[2])
    num_edges = int(line[3])
    tent = [0] * num_edges
    matrix = CSRImpl(size, size)
    for _ in xrange(num_edges):
        line = raw_input().split()
        if line[0] == 'a':
            line.pop(0)
        u, v, weight = [int(x) for x in line]
        matrix.set(u, v, weight)
    #print('A[1][0] = %d' % matrix.get(1, 0))
    #print('A[1][1] = %d' % matrix.get(1, 1))
    #print('A[2][2] = %d' % matrix.get(2, 2))
    #print('A[3][1] = %d' % matrix.get(3, 1))
    #matrix.debug_info()
    print matrix.iterate()
    matrix.print_dimacs()
    matrix.print_node_labels()
    print matrix.largest_out_degree()

def delta_step(graph, delta):
    pass

class CSRImpl:
    def __init__(self, numRows, numCols):
        self.value = []
        self.IA = [0] * (numRows + 1)
        self.JA = []
        self.node_labels = [INT_MAX] * numRows
        self.node_labels[0] = 0
        self.numRows = numRows
        self.numCols = numCols
        print('rows: %d' % numRows)
    def get(self, x, y):
        entries_in_row = self.IA[x + 1] - self.IA[x]
        #print('val[%d]: %d' % (self.IA[x], self.value[self.IA[x] + y]))
        #print('x: %d y: %d' % (x, y))
        for i in xrange(self.IA[x], self.IA[x+1]):
            if self.JA[i] == y:
                return self.value[i]
            #print('val[%d]: %d' % (i, self.value[i]))
        #offset = self.JA[entries_in_row] + y
        return 0
    def set(self, x, y, v):
        for i in range(x+1, self.numRows+1):
            print('IA size line27: %d' % len(self.IA))
            print('index of IA: %d' % i)
            self.IA[i] += 1
        previous_row_values_count = self.IA[x]
        inserted = False
        print('i: %d j: %d' % (previous_row_values_count, self.IA[x+1] - 1))
        for j in range(previous_row_values_count, self.IA[x+1]-1):
            print('Loop enter')
            print('Index: %d JA size: %d Val size: %d' % (j, len(self.JA), len(self.value)))
            if self.JA[j] > y:
                self.JA.insert(j, y)
                self.value.insert(j, v)
                inserted = True
                break
            elif self.JA[j] == y:
                inserted = True
                self.value[j] = v
                break
        if not inserted:
            print('Line 62: index: %d JA size: %d Val size: %d' % (self.IA[x+1]-1, len(self.JA), len(self.value)))
            self.JA.insert(self.IA[x+1]-1,y)
            self.value.insert(self.IA[x+1]-1, v)
        print("val: %s " % self.value)
        print("IA: %s " % self.IA)
        print("JA: %s " % self.JA)
    def iterate(self):
        result = [] # a list of triple (row, col, value)
        for i,v in enumerate(self.IA):
            if i == 0:
                continue
            current_row_index = 0
            while current_row_index < v-self.IA[i-1]:
                row_value = i - 1
                col_value = self.JA[self.IA[i-1] + current_row_index]
                real_value = self.value[self.IA[i-1] + current_row_index]
                result.append((row_value, col_value, real_value))
                current_row_index += 1
        return result

    def print_dimacs(self):
        print 'p sp %d %d' % (self.numRows, len(self.value))
        edges = self.iterate()
        for edge in edges:
            print 'a %d %d %d' % (edge[0], edge[1], edge[2])

    def print_node_labels(self):
        for i,v in enumerate(self.node_labels):
            print('%d -> %d' % (i, v))

    def largest_out_degree(self):
        old_degree = -1
        row = -1
        for i in xrange(self.numRows):
            curr_degree = self.IA[i + 1] - self.IA[i]
            if curr_degree > old_degree:
                row = i
                old_degree = curr_degree
        return row

    def cost(u, v):
        return self.get(u,v)

    def tent(u):
        return self.node_labels[u]

    def debug_info(self):
        print 'value ', self.value
        print 'IA ', self.IA
        print 'JA ', self.JA

if __name__ == '__main__':
    parse_input()
