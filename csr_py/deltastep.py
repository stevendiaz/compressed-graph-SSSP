import math
from random import shuffle
INT_MAX = 2147483647
relax_count = 0

def parse_input():
    line = raw_input().split()
    size = int(line[2])
    num_edges = int(line[3])
    matrix = CSRImpl(size, size)
    for _ in xrange(num_edges):
        line = raw_input().split()
        if line[0] == 'a':
            line.pop(0)
        u, v, weight = [int(x) for x in line]
        matrix.set(u, v, weight)
    delta_step(matrix, 1)

def delta_step(graph, delta):
    global relax_count
    relax_count = 0
    heavy = set()
    light = set()
    for vertex in graph.iterate():
        cost = vertex[2]
        if cost > delta:
            heavy.add(vertex)
        else:
            light.add(vertex)
        graph.set_tent(vertex[0], INT_MAX)
    graph.set_tent(1, 0)

    buckets = WorkList(graph, delta)
    while buckets.has_elements():
        S = set()
        i = buckets.get_index()
        while len(buckets.get(i)) > 0:
            req = match(graph, buckets.get(i), light)
            S = S.union(buckets.get(i))
            buckets.set(i, set())
            buckets.relax_nodes(graph, req)
        req = match(graph, S, heavy)
        buckets.relax_nodes(graph, req)
    graph.print_node_labels()

def relax(graph, buckets, w, d, delta):
    global relax_count
    relax_count += 1
    tent_cost = graph.get_tent(w)
    if d < tent_cost:
        graph.set_tent(w, d)
        i = math.floor(tent_cost/delta)
        if w in buckets[i]:
            buckets[i].remove(w)
        new_idx = math.floor(d/delta)
        if new_idx not in buckets.keys():
            buckets[new_idx] = set([w])
        else:
            buckets[new_idx].add(w)

def get_index(buckets):
    for key in buckets:
        if len(buckets[key]) > 0:
            return key

def match(graph, s, match_set):
    result = set()
    for edge in match_set:
        if edge[0] in s:
           result.add((edge[1], graph.get_tent(edge[0]) + edge[2]))
    return result


def has_elements(buckets):
    for i in buckets.keys():
        if len(buckets[i]) != 0:
            return True
    return False

class CSRImpl:
    def __init__(self, numRows, numCols):
        numRows += 1
        self.value = []
        self.IA = [0] * (numRows + 1)
        self.JA = []
        self.seen_nodes = {}
        self.node_labels = [0] * numRows
        self.numRows = numRows
        self.numCols = numCols

    def get(self, x, y):
        for i in xrange(self.IA[x], self.IA[x+1]):
            if self.JA[i] == y:
                return self.value[i]
        return 0

    def set(self, x, y, v):
        if (x,y) not in self.seen_nodes:
            for i in range(x+1, self.numRows+1):
                self.IA[i] += 1
            self.update_value(x, y, v)
        else:
            if v > self.get(x, y):
                self.update_value(x, y, v)

    def update_value(self, x, y, v):
        previous_row_values_count = self.IA[x]
        inserted = False
        for j in range(previous_row_values_count, self.IA[x+1] - 1):
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
        self.seen_nodes[(x,y)] = v


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
        for i in xrange(1, len(self.node_labels)):
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

class WorkList:
    def __init__(self, graph, delta):
        self.buckets = {}
        self.delta = delta
        for v in graph.iterate():
            i = math.floor(graph.get_tent(v[0])/delta)
            if i not in self.buckets:
                self.buckets[i] = set([v[0]])
            else:
                self.buckets[i].add(v[0])

    def has_elements(self):
        """
        Return False if for all the entry in buckets, the set is empty
        """
        for i in self.buckets.keys():
            if len(self.buckets[i]) != 0:
                return True
        return False

    def get_index(self):
        for key in self.buckets:
            if len(self.buckets[key]) > 0:
                return key
        return -1

    def get(self, i):
        return self.buckets[i]

    def set(self, i, nodes):
        self.buckets[i] = nodes

    def relax_nodes(self, graph, req):
        req_list = list(req)
        shuffle(req_list)
        for e in req_list:
            relax(graph, self.buckets, e[0], e[1], self.delta)


if __name__ == '__main__':
    parse_input()
