
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
        matrix.set(u - 1, v, weight)
    matrix.debug_info()
    print matrix.iterate()
    matrix.print_dimacs()

class CSRImpl:
    def __init__(self, numRows, numCols):
        self.value = []
        self.IA = [0] * (numRows + 1)
        self.JA = []
        self.numRows = numRows
        self.numCols = numCols
    def get(self, x, y):
        previous_row_values_count = self.IA[x]
        current_row_valid_count = self.IA[x+1]
        for i in range(previous_row_values_count, current_row_valid_count):
            if self.JA[i] == y:
                return self.value[i]
            else:
                return 0.0
    def set(self, x, y, v):
        for i in range(x+1, self.numRows+1):
            self.IA[i] += 1
        previous_row_values_count = self.IA[x]
        inserted = False
        for j in range(previous_row_values_count, self.IA[x+1]-1):
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
            self.JA.insert(self.IA[x+1]-1,y)
            self.value.insert(self.IA[x+1]-1, v)
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
            print 'a %d %d %d' % (edge[0] + 1, edge[1], edge[2])

    def debug_info(self):
        print 'value ', self.value
        print 'IA ', self.IA
        print 'JA ', self.JA

if __name__ == '__main__':
    parse_input()
