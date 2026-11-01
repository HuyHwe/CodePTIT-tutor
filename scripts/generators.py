"""Random small-input generators for stress testing, one per input format.

Each generator is f(rng, size) -> input text, where size grows from 1 to ~6 during a
stress run so the first failing input found is small and easy to trace by hand.
Problems are mapped to generators in courses/<id>/course.json ("generators").
Inputs must respect the statement's constraints (the reference only promises to be
correct on valid inputs).
"""

NO_EDGE = 10000  # value CodePTIT TRR2 statements use for "no edge" in weight matrices


# ------------------------------------------------------------------ helpers

def _n(rng, size, lo=2, extra=2):
    return rng.randint(lo, lo + size + extra)


def _matrix(rows):
    return "\n".join(" ".join(str(x) for x in r) for r in rows)


def _adj(rng, n, directed, p=None):
    p = rng.choice([0.2, 0.35, 0.5, 0.7]) if p is None else p
    a = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i == j or (not directed and j < i):
                continue
            if rng.random() < p:
                a[i][j] = 1
                if not directed:
                    a[j][i] = 1
    return a


def _rows(a, n):
    return [a[i][1:n + 1] for i in range(1, n + 1)]


def _wmatrix(rng, n, directed, lo=1, hi=50, negative=False):
    a = _adj(rng, n, directed)
    w = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i == j:
                continue
            if not directed and j < i:
                w[i][j] = w[j][i]
                continue
            if a[i][j]:
                x = rng.randint(lo, hi)
                if negative and rng.random() < 0.3:
                    x = -x
                w[i][j] = x
            else:
                w[i][j] = NO_EDGE
    return _rows(w, n)


def _edges(rng, n, directed):
    a = _adj(rng, n, directed=False)
    e = [(i, j) for i in range(1, n + 1) for j in range(i + 1, n + 1) if a[i][j]]
    if not e:
        i = rng.randint(1, n - 1)
        e = [(i, rng.randint(i + 1, n))]
    rng.shuffle(e)
    return e


def _t(rng):
    return rng.choice([1, 2])


# ------------------------------------------------------------------ TRR2: representations

def rep_matrix(directed):
    def gen(rng, size):
        n = _n(rng, size, 1)
        return f"{_t(rng)}\n{n}\n{_matrix(_rows(_adj(rng, n, directed), n))}\n"
    return gen


def rep_edges(directed):
    def gen(rng, size):
        n = _n(rng, size)
        e = _edges(rng, n, directed)
        return f"{_t(rng)}\n{n} {len(e)}\n" + "\n".join(f"{u} {v}" for u, v in e) + "\n"
    return gen


def rep_adjlist(directed):
    def gen(rng, size):
        n = _n(rng, size, 1)
        a = _adj(rng, n, directed)
        lines = []
        for i in range(1, n + 1):
            ke = [j for j in range(1, n + 1) if a[i][j]]
            lines.append(" ".join(map(str, [len(ke)] + ke)))
        return f"{_t(rng)}\n{n}\n" + "\n".join(lines) + "\n"
    return gen


def rep_wmatrix(directed):
    def gen(rng, size):
        n = _n(rng, size, 1)
        return f"{_t(rng)}\n{n}\n{_matrix(_wmatrix(rng, n, directed))}\n"
    return gen


def rep_wedges(directed):
    def gen(rng, size):
        n = _n(rng, size)
        e = _edges(rng, n, directed)
        return f"{_t(rng)}\n{n} {len(e)}\n" + "\n".join(f"{u} {v} {rng.randint(1, 50)}" for u, v in e) + "\n"
    return gen


# ------------------------------------------------------------------ TRR2: search / connectivity

def matrix_only(directed):
    def gen(rng, size):
        n = _n(rng, size)
        return f"{n}\n{_matrix(_rows(_adj(rng, n, directed), n))}\n"
    return gen


def path_tuv(rng, size):
    n = _n(rng, size)
    u, v = rng.sample(range(1, n + 1), 2)
    return f"{_t(rng)}\n{n} {u} {v}\n{_matrix(_rows(_adj(rng, n, False), n))}\n"


def _euler_graph(rng, n, directed):
    """Union of random edge-disjoint cycles -> every vertex even (or balanced)."""
    for _ in range(200):
        a = [[0] * (n + 1) for _ in range(n + 1)]
        for _ in range(rng.randint(1, 3)):
            k = rng.randint(3 if not directed else 2, n)
            cyc = rng.sample(range(1, n + 1), k)
            pairs = list(zip(cyc, cyc[1:] + cyc[:1]))
            if any(a[u][v] or (not directed and a[v][u]) for u, v in pairs):
                continue
            for u, v in pairs:
                a[u][v] = 1
                if not directed:
                    a[v][u] = 1
        used = [i for i in range(1, n + 1) if any(a[i][1:]) or any(a[j][i] for j in range(1, n + 1))]
        if len(used) == n and _connected(a, n):
            return a
    return None


def _connected(a, n):
    seen, st = {1}, [1]
    while st:
        u = st.pop()
        for v in range(1, n + 1):
            if (a[u][v] or a[v][u]) and v not in seen:
                seen.add(v)
                st.append(v)
    return len(seen) == n


def euler(directed):
    def gen(rng, size):
        n = rng.randint(3, 3 + size)
        if rng.random() < 0.5:
            return f"1\n{n}\n{_matrix(_rows(_adj(rng, n, directed), n))}\n"
        a = _euler_graph(rng, n, directed)
        if a is None:
            return f"1\n{n}\n{_matrix(_rows(_adj(rng, n, directed), n))}\n"
        return f"2\n{n} {rng.randint(1, n)}\n{_matrix(_rows(a, n))}\n"
    return gen


def hamilton(rng, size):
    n = rng.randint(3, 3 + min(size, 4))
    return f"{n} {rng.randint(1, n)}\n{_matrix(_rows(_adj(rng, n, False, p=rng.choice([0.5, 0.7, 0.9])), n))}\n"


def tree_ts(rng, size):
    n = _n(rng, size)
    return f"{_t(rng)}\n{n} {rng.randint(1, n)}\n{_matrix(_rows(_adj(rng, n, False), n))}\n"


def prim(rng, size):
    n = _n(rng, size)
    return f"{n} {rng.randint(1, n)}\n{_matrix(_wmatrix(rng, n, False, hi=rng.choice([3, 50])))}\n"


def kruskal(rng, size):
    n = _n(rng, size)
    e = _edges(rng, n, False)
    hi = rng.choice([3, 50])  # small weights -> many ties, exposes ordering bugs
    return f"{n} {len(e)}\n" + "\n".join(f"{u} {v} {rng.randint(1, hi)}" for u, v in e) + "\n"


def shortest_st(negative):
    def gen(rng, size):
        n = _n(rng, size)
        s, t = rng.sample(range(1, n + 1), 2)
        return f"{n} {s} {t}\n{_matrix(_wmatrix(rng, n, True, hi=rng.choice([5, 50]), negative=negative))}\n"
    return gen


def floyd(rng, size):
    n = _n(rng, size)
    return f"{n}\n{_matrix(_wmatrix(rng, n, True, hi=rng.choice([3, 50])))}\n"


# ------------------------------------------------------------------ TRR1

def _real(rng):
    return rng.choice([0, 0, 0, rng.randint(-5, 5), round(rng.uniform(-10, 10), 1)])


def reals(k):
    def gen(rng, size):
        return " ".join(f"{_real(rng):.1f}" for _ in range(k)) + "\n"
    return gen


def two_sets(rng, size):
    n = rng.randint(1, 3 + size * 2)
    row = lambda: " ".join(str(rng.randint(0, 1)) for _ in range(n))
    return f"{n}\n{row()}\n{row()}\n"


def count_abkm(rng, size):
    hi = rng.choice([30, 1000, 1 << 18])
    a = rng.randint(1, hi)
    b = rng.randint(a, hi)
    return f"{a} {b} {rng.randint(1, hi)} {rng.randint(1, hi)}\n"


def one_int(hi):
    def gen(rng, size):
        return f"{rng.randint(1, rng.choice([10, 100, hi]))}\n"
    return gen


def n_k_50(rng, size):
    n = rng.randint(2, rng.choice([6, 20, 50]))
    return f"{n} {rng.randint(2, n)}\n"


def n_s_50(rng, size):
    n = rng.randint(1, rng.choice([6, 20, 50]))
    return f"{n} {rng.randint(1, n)}\n"


def perm_prev(rng, size):
    n = rng.randint(3, 3 + size)
    p = list(range(1, n + 1))
    rng.shuffle(p)
    if rng.random() < 0.2:
        p.sort()  # first permutation: there is no previous one
    return f"{n}\n{' '.join(map(str, p))}\n"


def comb_prev(rng, size):
    n = rng.randint(3, 3 + size)
    k = rng.randint(1, n)
    c = sorted(rng.sample(range(1, n + 1), k))
    if rng.random() < 0.2:
        c = list(range(1, k + 1))
    return f"{n} {k}\n{' '.join(map(str, c))}\n"


def perm_next_t(rng, size):
    n = rng.randint(3, 3 + size)
    p = list(range(1, n + 1))
    rng.shuffle(p)
    if rng.random() < 0.2:
        p.sort(reverse=True)
    return f"{n} {rng.randint(1, 8)}\n{' '.join(map(str, p))}\n"


def bits_next_t(rng, size):
    n = rng.randint(3, 3 + size)
    x = [rng.randint(0, 1) for _ in range(n)]
    if rng.random() < 0.2:
        x = [rng.choice([0, 1])] * n
    return f"{n} {rng.randint(3, 10)}\n{' '.join(map(str, x))}\n"


def perm_fixed(rng, size):
    n = rng.randint(3, 3 + min(size, 4))
    p = list(range(1, n + 1))
    rng.shuffle(p)
    k = rng.randint(1, n)
    pos = rng.sample(range(1, n + 1), k)
    lines = [f"{u} {p[u - 1]}" for u in pos]
    return f"{n} {k}\n" + "\n".join(lines) + "\n"


def comb_nkt(rng, size):
    n = rng.randint(3, 3 + min(size, 5))
    return f"{n} {rng.randint(1, n)} {rng.randint(1, n)}\n"


def bits_fixed(rng, size):
    n = rng.randint(3, 3 + min(size, 6))
    k = rng.randint(1, n)
    pos = rng.sample(range(1, n + 1), k)
    return f"{n} {k}\n" + "\n".join(f"{u} {rng.randint(0, 1)}" for u in pos) + "\n"


def knapsack(rng, size):
    n = rng.randint(1, 3 + size)
    hi = rng.choice([5, 20])
    items = [(rng.randint(1, hi), rng.randint(1, hi)) for _ in range(n)]
    b = rng.randint(1, sum(w for w, _ in items))
    return f"{n} {b}\n" + "\n".join(f"{w} {v}" for w, v in items) + "\n"


def cost_matrix(zero_diag, max_n=8):
    def gen(rng, size):
        n = rng.randint(2, min(max_n, 2 + size))
        hi = rng.choice([3, 9, 100])  # small values -> ties
        rows = [[0 if (zero_diag and i == j) else rng.randint(1, hi) for j in range(n)] for i in range(n)]
        return f"{n}\n{_matrix(rows)}\n"
    return gen


def balls(rng, size):
    return f"{rng.randint(1, 50)} {rng.randint(1, 50)} {rng.randint(1, 50)} {rng.randint(2, 20)}\n"


def nmp(rng, size):
    m = rng.randint(2, rng.choice([10, 1000, 1 << 18]))
    return f"{rng.randint(1, rng.choice([20, 1 << 18]))} {m} {rng.randint(0, m - 1)}\n"


def nk_1e4(rng, size):
    return f"{rng.randint(1, rng.choice([10, 100, 10000]))} {rng.randint(1, rng.choice([10, 10000]))}\n"


# ------------------------------------------------------------------ registry

GENERATORS = {
    # TRR2
    "rep_matrix_ud": rep_matrix(False), "rep_matrix_d": rep_matrix(True),
    "rep_edges_ud": rep_edges(False), "rep_edges_d": rep_edges(True),
    "rep_adjlist_ud": rep_adjlist(False), "rep_adjlist_d": rep_adjlist(True),
    "rep_wmatrix_ud": rep_wmatrix(False), "rep_wmatrix_d": rep_wmatrix(True),
    "rep_wedges_ud": rep_wedges(False), "rep_wedges_d": rep_wedges(True),
    "path_tuv": path_tuv,
    "matrix_ud": matrix_only(False), "matrix_d": matrix_only(True),
    "euler_ud": euler(False), "euler_d": euler(True),
    "hamilton": hamilton, "tree_ts": tree_ts, "prim": prim, "kruskal": kruskal,
    "dijkstra": shortest_st(False), "bellman": shortest_st(True), "floyd": floyd,
    # TRR1
    "reals2": reals(2), "reals3": reals(3), "two_sets": two_sets,
    "count_abkm": count_abkm, "int_2p18": one_int(1 << 18), "int_1e4": one_int(10000),
    "n_k_50": n_k_50, "n_s_50": n_s_50,
    "perm_prev": perm_prev, "comb_prev": comb_prev, "perm_next_t": perm_next_t,
    "bits_next_t": bits_next_t, "perm_fixed": perm_fixed, "comb_nkt": comb_nkt,
    "bits_fixed": bits_fixed, "knapsack": knapsack,
    "cost_matrix": cost_matrix(False), "cost_matrix_tsp": cost_matrix(True),
    "balls": balls, "nmp": nmp, "nk_1e4": nk_1e4,
}


def get(name):
    return GENERATORS.get(name)
