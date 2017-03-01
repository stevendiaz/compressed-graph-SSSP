import math
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
    delta_step(matrix, 1)

def delta_step(graph, delta):
    heavy = set()
    light = set()
    for vertex in graph.iterate():
        cost = vertex[2]
        if cost > delta:
            heavy.add(vertex)
        else:
            light.add(vertex)
        graph.set_tent(vertex[0], INT_MAX)
    graph.set_tent(0, 0)

    buckets = make_buckets(graph, delta)
    while has_elements(buckets):
        S = set()
        i = get_index(buckets)
        while len(buckets[i]) > 0:
            req = light_matches(graph, buckets[i], light)
            S = S.union(buckets[i])
            buckets[i] = set()
            for e in req:
                relax(graph, buckets, e[0], e[1], delta)
        req = heavy_matches(graph, S, heavy)
        for e in req:
            relax(graph, buckets, e[0], e[1], delta)
    graph.print_node_labels()

def relax(graph, buckets, w, d, delta):
    tent_cost = graph.get_tent(w)
    if d < tent_cost:
        graph.set_tent(w, d)
        i = math.floor(tent_cost/delta)
        buckets[i].remove(w)
        new_idx = math.floor(d/delta)
        if new_idx not in buckets:
            buckets[new_idx] = set([w])
        else:
            buckets[new_idx].add(w)

def get_index(buckets):
    for key in buckets:
        if len(buckets[key]) > 0:
            return key

def make_buckets(graph, delta):
    B = {}
    for v in graph.iterate():
        i = math.floor(graph.get_tent(v[0])/delta)
        if i not in B:
            B[i] = set([v[0]])
        else:
            B[i].add(v[0])
    return B

def heavy_matches(graph, S, heavy):
    result = set()
    for edge in heavy:
        if edge[0] in S:
           result.add((edge[1], graph.get_tent(edge[0]) + edge[2]))
    return result

def light_matches(graph, bucket, light):
    result = set()
    for edge in light:
        if edge[0] in bucket:
            result.add((edge[1], graph.get_tent(edge[0]) + edge[2]))
    return result

def has_elements(buckets):
    """
    Return False if for all the entry in buckets, the set is empty
    """
    for i in buckets.keys():
        if len(buckets[i]) != 0:
            return True
    return False

class CSRImpl:
    def __init__(self, numRows, numCols):
        self.value = []
        self.IA = [0] * (numRows + 1)
        self.JA = []
        self.node_labels = [0] * numRows
        self.numRows = numRows
        self.numCols = numCols
    def get(self, x, y):
        entries_in_row = self.IA[x + 1] - self.IA[x]
        for i in xrange(self.IA[x], self.IA[x+1]):
            if self.JA[i] == y:
                return self.value[i]
        return 0
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
            print 'a %d %d %d' % (edge[0], edge[1], edge[2])

    def print_node_labels(self):
        for i in xrange(len(self.node_labels)):
            print('%d -> %d' % (i, self.node_labels[i]))

    def largest_out_degree(self):
        old_degree = -1
        row = -1
        for i in xrange(self.numRows):
            curr_degree = self.IA[i + 1] - self.IA[i]
            if curr_degree > old_degree:
                row = i
                old_degree = curr_degree
        return row

    def cost(self, u, v):
        return self.get(u,v)

    def get_tent(self, u):
        return self.node_labels[u]

    def set_tent(self, u, value):
        self.node_labels[u] = value

    def debug_info(self):
        print 'value ', self.value
        print 'IA ', self.IA
        print 'JA ', self.JA

if __name__ == '__main__':
    parse_input()
