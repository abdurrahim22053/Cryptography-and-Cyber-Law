

Name: MD. Abdur Rahim
Student ID: IT22053





📑 Table of Contents (All Covered Topics)

Evolution of Number Systems & Scope of Number Theory

Divisibility, Formal Proofs & Division with Remainders

Modular Arithmetic, Congruence Relations & Cayley Tables

Greatest Common Divisor (GCD), Naive vs. Euclid's Algorithm & Complexity Analysis

Extended Euclidean Algorithm, Bézout's Identity & GCD Certificates

Least Common Multiple (LCM) & Relationship with GCD

Linear Diophantine Equations: Existence, Particular & General Solutions

Modular Inverses, Modular Division & Field Structure of $\mathbb{Z}_p$

Remainder Dependency & The Chinese Remainder Theorem (CRT)

Fast Modular Exponentiation (Binary Exponentiation / Exponentiation by Squaring)

Fermat's Little Theorem (FLT): Cycle Graph Proof & Optimization

Euler's Totient Function $\phi(n)$ & Euler's Generalization Theorem

Prime Numbers: Eight Classic Proofs of Infinitude

Distribution of Primes, Prime Number Theorem & Famous Conjectures

Primality Testing, Sieve of Eratosthenes, Wheel Factorization & Lucas's Theorem

Fermat Pseudoprimes, Carmichael Numbers & Korselt's Criterion

Special Primes: Mersenne Primes, Lucas-Lehmer Test, Perfect Numbers & Antiprimes

Cryptographic Synthesis: Symmetric vs. Asymmetric Encryption & Full RSA Implementation

1. Evolution of Number Systems & Scope of Number Theory

Mathematics begins with counting discrete objects, giving rise to progressively richer algebraic structures as we demand closure under inverse operations:

$$\mathbb{N} \subset \mathbb{Z} \subset \mathbb{Q} \subset \mathbb{R} \subset \mathbb{C}$$

Number Set

Symbol

Elements

Closed Under

Fails Under

Natural Numbers

$\mathbb{N}$

$\{1, 2, 3, \dots\}$

Addition ($+$), Multiplication ($\times$)

Subtraction ($2 - 3 \notin \mathbb{N}$), Division

Integers

$\mathbb{Z}$

$\{\dots, -2, -1, 0, 1, 2, \dots\}$

Addition ($+$), Subtraction ($-$), Multiplication ($\times$)

Division ($3 / 2 \notin \mathbb{Z}$)

Rational Numbers

$\mathbb{Q}$

$\{\frac{a}{b} \mid a, b \in \mathbb{Z}, b \neq 0\}$

$+, -, \times, \div$ (except division by $0$)

Limits / Irrational roots ($\sqrt{2} \notin \mathbb{Q}$)

Why Number Theory Matters Today

Classical View: Mathematicians like G.H. Hardy celebrated number theory as the purest, most "useless" branch of mathematics, uncorrupted by real-world application.

Modern Reality: As Donald Knuth noted, virtually every theorem in elementary number theory arises naturally when making computers perform high-speed exact integer arithmetic. Furthermore, number theory underpins Public-Key Cryptography (RSA, Diffie-Hellman, Elliptic Curves), securing online banking, messaging, TLS/HTTPS, and digital signatures billions of times daily.

2. Divisibility, Formal Proofs & Division with Remainders

Formal Definition of Divisibility

Let $a, b \in \mathbb{Z}$ with $b \neq 0$. We say $b$ divides $a$ (written $b \mid a$, or "$a$ is a multiple of $b$") if there exists an integer $k \in \mathbb{Z}$ such that:


$$a = b \times k$$


If no such integer $k$ exists, we write $b \nmid a$.

Fundamental Divisibility Lemmas & Proofs

Linearity Lemma: If $c \mid a$ and $c \mid b$, then $c \mid (ax + by)$ for all integers $x, y \in \mathbb{Z}$.

Proof: Since $c \mid a$ and $c \mid b$, we have $a = c k_1$ and $b = c k_2$ for some $k_1, k_2 \in \mathbb{Z}$. Thus:


$$ax + by = (c k_1)x + (c k_2)y = c(k_1 x + k_2 y)$$


Since $k_1 x + k_2 y \in \mathbb{Z}$, it follows by definition that $c \mid (ax + by)$. $\blacksquare$

Transitivity Lemma: If $a \mid b$ and $b \mid c$, then $a \mid c$.

Proof: $b = a k_1$ and $c = b k_2 \implies c = a(k_1 k_2) \implies a \mid c$. $\blacksquare$

The Division Algorithm (Division with Remainder)

For any integer $a \in \mathbb{Z}$ and positive integer $b \in \mathbb{Z}^+$, there exist unique integers $q$ (quotient) and $r$ (remainder) satisfying:


$$a = q \times b + r, \quad \text{with } 0 \le r < b$$

Positive Example: $a = 15, b = 4 \implies 15 = 3 \times 4 + 3$ ($q = 3, r = 3$).

Negative Dividend Example: $a = -13, b = 3 \implies -13 = (-5) \times 3 + 2$ ($q = -5, r = 2$). Note that $r$ must satisfy $0 \le r < 3$, so $-13 = (-4)\times 3 - 1$ is invalid because $-1 < 0$.

Connection Lemma

Two integers $a_1$ and $a_2$ leave the exact same remainder when divided by $b$ if and only if $b \mid (a_1 - a_2)$.

def division_with_remainder(a: int, b: int) -> tuple[int, int]:
    """
    Computes unique quotient q and non-negative remainder r such that:
    a = q * b + r, where 0 <= r < b.
    """
    assert b > 0, "Divisor b must be strictly positive."
    q = a // b  # Python's floor division automatically satisfies 0 <= a % b < b
    r = a % b
    assert a == q * b + r and 0 <= r < b
    return q, r

print("15 / 4  ->", division_with_remainder(15, 4))    # (3, 3)
print("-13 / 3 ->", division_with_remainder(-13, 3))   # (-5, 2)


3. Modular Arithmetic, Congruence Relations & Cayley Tables

Congruence Relation

For a positive integer modulus $m > 0$, we say $a$ is congruent to $b$ modulo $m$, written:


$$a \equiv b \pmod{m}$$


if and only if $m \mid (a - b)$ (equivalently, $a \bmod m = b \bmod m$). The set of all integers congruent to $a$ forms the residue class $[a]_m = \{a + km \mid k \in \mathbb{Z}\}$.

Compatibility with Arithmetic Operations

If $a \equiv b \pmod{m}$ and $c \equiv d \pmod{m}$, then:

Addition: $a + c \equiv b + d \pmod{m}$

Subtraction: $a - c \equiv b - d \pmod{m}$

Multiplication: $a \times c \equiv b \times d \pmod{m}$

Exponentiation: $a^n \equiv b^n \pmod{m}$ for all $n \in \mathbb{N}$

Classic Applications

Evaluating Huge Expressions: Find $(17 \times (12 \times 19 + 5) - 23) \bmod 3$.

Using positive residues $\{0, 1, 2\}$: $2 \times (0 \times 1 + 2) - 2 = 4 - 2 = 2 \pmod{3}$.

Using balanced residues $\{-1, 0, 1\}$: $(-1) \times (0 \times 1 - 1) - (-1) = 1 + 1 = 2 \pmod{3}$.

Last Two Digits of $99^{99}$: Since $99 \equiv -1 \pmod{100}$:


$$99^{99} \equiv (-1)^{99} \equiv -1 \equiv 99 \pmod{100}$$

Divisibility Rule for 3 and 9: Since $10 \equiv 1 \pmod{3}$ and $10 \equiv 1 \pmod{9}$, $10^k \equiv 1 \pmod{3, 9}$ for all $k \ge 0$. Thus, any base-10 integer $N = \sum_{i=0}^d c_i 10^i$ satisfies:


$$N \equiv \sum_{i=0}^d c_i \pmod{3 \text{ and } 9}$$

Cayley Tables: Prime Modulus ($\mathbb{Z}_7$) vs. Composite Modulus ($\mathbb{Z}_6$)

Multiplication Modulo 7 (Prime)          Multiplication Modulo 6 (Composite)
× | 0 1 2 3 4 5 6                        × | 0 1 2 3 4 5
--+--------------                        --+------------
0 | 0 0 0 0 0 0 0                        0 | 0 0 0 0 0 0
1 | 0 1 2 3 4 5 6  <-- Permutation       1 | 0 1 2 3 4 5
2 | 0 2 4 6 1 3 5  <-- Permutation       2 | 0 2 4 0 2 4  <-- Zero divisors! (2*3 ≡ 0)
3 | 0 3 6 2 5 1 4  <-- Permutation       3 | 0 3 0 3 0 3  <-- Missing 1, 2, 4, 5!
4 | 0 4 1 5 2 6 3  <-- Permutation       4 | 0 4 2 0 4 2
5 | 0 5 3 1 6 4 2  <-- Permutation       5 | 0 5 4 3 2 1
6 | 0 6 5 4 3 2 1  <-- Permutation


Notice that in $\mathbb{Z}_7$, every non-zero row is a complete permutation of $\{1, 2, 3, 4, 5, 6\}$, meaning every non-zero element has a unique multiplicative inverse. In $\mathbb{Z}_6$, rows $2, 3, 4$ contain zeros and fail to cover all residues—making division by $2, 3,$ or $4$ impossible modulo $6$.

def print_mod_table(m: int, op: str = '*'):
    """Generates and prints modular addition or multiplication tables."""
    header = f"{op} | " + " ".join(f"{j:2d}" for j in range(m))
    print(header)
    print("-" * len(header))
    for i in range(m):
        row_vals = [(i * j) % m if op == '*' else (i + j) % m for j in range(m)]
        print(f"{i} | " + " ".join(f"{val:2d}" for val in row_vals))

print_mod_table(7, '*')


4. Greatest Common Divisor (GCD), Naive vs. Euclid's Algorithm & Complexity Analysis

Definition

The Greatest Common Divisor, $\gcd(a, b)$, of integers $a$ and $b$ (not both zero) is the largest positive integer $d$ such that $d \mid a$ and $d \mid b$. By convention, $\gcd(a, 0) = \vert{}a\vert{}$.

Algorithmic Progression

Naive Trial Search: Iterate $d$ from $\min(a, b)$ down to $1$ and return the first $d$ dividing both.

Complexity: $O(\min(a, b))$ divisions. For 100-digit numbers ($\approx 10^{100}$), even a supercomputer performing $10^{15}$ ops/sec would take $> 10^{77}$ years!

Subtraction-Based Euclid: Uses the lemma $\gcd(a, b) = \gcd(a - b, b)$ for $a \ge b$.

Bottleneck: Still slow if $a \gg b$, e.g., $\gcd(790933790548, 7)$ takes over $10^{11}$ subtractions.

Modulo-Based Euclid's Algorithm: Replaces repeated subtraction with remainder:


$$\gcd(a, b) = \gcd(b, a \bmod b)$$

Mathematical Proof of Logarithmic Runtime

Lemma: If $a \ge b > 0$, then $a \bmod b < \frac{a}{2}$.

Case 1 ($b \le \frac{a}{2}$): By definition of remainder, $a \bmod b < b \le \frac{a}{2}$.

Case 2 ($b > \frac{a}{2}$): Since $\frac{a}{2} < b \le a$, $b$ goes into $a$ exactly once, so $a \bmod b = a - b < a - \frac{a}{2} = \frac{a}{2}$. $\blacksquare$

Consequently, every two iterations reduce both numbers by at least half, yielding a worst-case step count bounded by:


$$\text{Iterations} \le 2 \log_2(\min(a, b))$$


Even for 5,000-digit integers ($a < 10^{5000}$), Euclid's algorithm finishes in fewer than $16,610$ iterations!

def gcd_euclid_logged(a: int, b: int, verbose: bool = False) -> int:
    """Computes gcd(a, b) using Euclid's algorithm with optional step logging."""
    assert a >= 0 and b >= 0 and (a + b) > 0
    steps = 0
    while b > 0:
        if verbose:
            print(f"Step {steps:2d}: gcd({a}, {b})")
        a, b = b, a % b
        steps += 1
    if verbose:
        print(f"Step {steps:2d}: gcd({a}, {b}) -> Result = {a}")
    return a

gcd_euclid_logged(790933790547, 1849639579327, verbose=True)


5. Extended Euclidean Algorithm, Bézout's Identity & GCD Certificates

Certificate of Optimality

How can someone prove to you that $d = \gcd(a, b)$ without making you re-run the entire algorithm?

Checking $d \mid a$ and $d \mid b$ proves $d$ is a common divisor ($d \le \gcd(a, b)$).

Providing integers $x, y \in \mathbb{Z}$ such that $ax + by = d$ proves $\gcd(a, b) \le d$ (because any common divisor of $a$ and $b$ must divide $ax + by = d$).

Together, these two conditions form a Certificate of GCD.

Bézout's Identity & Recursive Back-Substitution

For any integers $a, b$ (not both zero), there exist integers $x, y$ such that:


$$ax + by = \gcd(a, b)$$

Given $d = \gcd(b, a \bmod b) = bp + (a \bmod b)q$, substituting $a \bmod b = a - \left\lfloor \frac{a}{b} \right\rfloor b$ gives:


$$d = bp + \left(a - \left\lfloor \frac{a}{b} \right\rfloor b\right)q = a(q) + b\left(p - \left\lfloor \frac{a}{b} \right\rfloor q\right)$$

def extended_gcd(a: int, b: int) -> tuple[int, int, int]:
    """
    Returns (d, x, y) such that d = gcd(a, b) and a*x + b*y = d.
    """
    if b == 0:
        return a, 1, 0
    d, p, q = extended_gcd(b, a % b)
    x = q
    y = p - (a // b) * q
    return d, x, y

d, x, y = extended_gcd(239, 201)
print(f"gcd(239, 201) = {d} = 239*({x}) + 201*({y})")  # 1 = 239*(-37) + 201*(44)


6. Least Common Multiple (LCM) & Relationship with GCD

The Least Common Multiple, $\text{lcm}(a, b)$, of positive integers $a, b$ is the smallest positive integer divisible by both $a$ and $b$.

Fundamental Identity

$$\text{lcm}(a, b) \cdot \gcd(a, b) = a \cdot b \implies \text{lcm}(a, b) = \frac{a}{\gcd(a, b)} \cdot b$$


(Note: Dividing $a$ by $\gcd(a, b)$ before multiplying by $b$ prevents intermediate integer overflow in fixed-width languages.)

def lcm(a: int, b: int) -> int:
    assert a > 0 and b > 0
    d, _, _ = extended_gcd(a, b)
    return (a // d) * b

print("lcm(531441, 262144) =", lcm(531441, 262144))  # 139314069504


7. Linear Diophantine Equations: Existence, Particular & General Solutions

A Linear Diophantine Equation seeks integer solutions $(x, y) \in \mathbb{Z}^2$ to:


$$ax + by = c$$

Complete Characterization Theorem

Let $d = \gcd(a, b)$, with $a = dp$ and $b = dq$ (so $\gcd(p, q) = 1$).

Existence Criterion: Solutions exist if and only if $d \mid c$.

Example: $187x + 55y = 121$ has solutions because $\gcd(187, 55) = 11$ and $11 \mid 121$.

Example: $187x + 55y = 45$ has no integer solutions because $11 \nmid 45$.

Particular Solution: If $c = t_0 d$ and $a\bar{x} + b\bar{y} = d$, then $(x_0, y_0) = (t_0 \bar{x}, t_0 \bar{y})$.

General Family of All Solutions: Every integer solution is parameterized by $t \in \mathbb{Z}$:


$$x = x_0 + tq = x_0 + t\frac{b}{d}, \qquad y = y_0 - tp = y_0 - t\frac{a}{d}$$

Real-World Application: Making Exact Change

Suppose an apple costs $22$ pesos. You only have $3$-peso bills ($x$), and the cashier only has $5$-peso bills ($y$). We solve $3x - 5y = 22$ with $x \ge 0, y \ge 0$:

Particular solution: $3(9) - 5(1) = 22 \implies (x_0, y_0) = (9, 1)$.

General solution: $x = 9 + 5t, \; y = 1 + 3t$ for $t \ge 0$ (e.g., $9$ bills of $3$ minus $1$ bill of $5$, or $14$ bills of $3$ minus $4$ bills of $5$).

def solve_diophantine(a: int, b: int, c: int):
    """
    Solves ax + by = c over integers.
    Returns ((x0, y0), (step_x, step_y)) or None if unsolvable.
    """
    d, x_bar, y_bar = extended_gcd(abs(a), abs(b))
    if c % d != 0:
        return None
    x_bar *= (1 if a >= 0 else -1)
    y_bar *= (1 if b >= 0 else -1)
    scale = c // d
    x0, y0 = x_bar * scale, y_bar * scale
    return (x0, y0), (b // d, -(a // d))

base, step = solve_diophantine(3, -5, 22)
print("Solutions for 3x - 5y = 22 (t = 0, 1, 2):")
for t in range(3):
    print(f"  t={t}: x = {base[0] + t*step[0]}, y = {base[1] + t*step[1]}")


8. Modular Inverses, Modular Division & Field Structure of $\mathbb{Z}_p$

Multiplicative Inverse Modulo $n$

An integer $\bar{a}$ is the multiplicative inverse of $a$ modulo $n$ (denoted $a^{-1} \bmod n$) if:


$$a \cdot \bar{a} \equiv 1 \pmod{n}$$

Existence Theorem: $a^{-1} \bmod n$ exists if and only if $\gcd(a, n) = 1$.

Proof: $ax \equiv 1 \pmod{n} \iff ax + ny = 1$ for some $y \in \mathbb{Z}$, which is solvable iff $\gcd(a, n) \mid 1 \iff \gcd(a, n) = 1$. $\blacksquare$

Uniqueness Lemma: If $x$ and $y$ are both inverses of $a \pmod{n}$, then:


$$x \equiv x(ay) \equiv (xa)y \equiv y \pmod{n}$$

Finite Fields ($\mathbb{Z}_p$): When $n = p$ is prime, every non-zero residue $\{1, 2, \dots, p-1\}$ is coprime to $p$ and thus invertible. Hence $\mathbb{Z}_p$ forms a finite field $\mathbb{F}_p$.

Modular Division Algorithm

To compute $x \equiv \frac{b}{a} \pmod{n}$ when $\gcd(a, n) = 1$:

Run extended_gcd(a, n) to obtain $as + nt = 1$.

Then $s \equiv a^{-1} \pmod{n}$.

Compute $x = (b \cdot s) \bmod n$.

def mod_inverse(a: int, n: int) -> int:
    d, x, _ = extended_gcd(a % n, n)
    if d != 1:
        raise ValueError(f"Inverse does not exist: gcd({a}, {n}) = {d}")
    return x % n

def mod_divide(b: int, a: int, n: int) -> int:
    return (b * mod_inverse(a, n)) % n

print("7 / 2 mod 9 =", mod_divide(7, 2, 9))  # 8 (Check: 8 * 2 = 16 ≡ 7 mod 9)


9. Remainder Dependency & The Chinese Remainder Theorem (CRT)

When Are Remainders Independent?

Dependent Moduli ($\gcd(a, b) > 1$):

Knowing $n \bmod 4$ completely determines $n \bmod 2$ (because $2 \mid 4$).

Knowing $n \equiv 1 \pmod{6}$ restricts $n \bmod 4$ to only $\{1, 3\}$ (since $n$ must be odd), never $\{0, 2\}$.

Independent Moduli ($\gcd(a, b) = 1$):

Knowing $n \bmod 3$ tells us nothing about $n \bmod 2$; all $3 \times 2 = 6$ pairs $(r_3, r_2)$ occur equally often.

The Chinese Remainder Theorem (CRT)

Let $m_1, m_2, \dots, m_k$ be pairwise coprime positive integers ($\gcd(m_i, m_j) = 1$ for $i \neq j$), and let $M = \prod_{i=1}^k m_i$. The system of congruences:


$$x \equiv r_i \pmod{m_i} \quad \text{for } i = 1, \dots, k$$


has a unique solution modulo $M$, explicitly constructed via Garner / Lagrange CRT:


$$x \equiv \sum_{i=1}^k r_i M_i y_i \pmod{M}, \quad \text{where } M_i = \frac{M}{m_i} \text{ and } y_i \equiv M_i^{-1} \pmod{m_i}$$

Application: Parallel Big-Integer Arithmetic

Instead of multiplying massive 10,000-bit integers directly, computers can represent them by their residues modulo several word-sized primes $p_1, \dots, p_k$, perform additions and multiplications independently in parallel across cores, and reconstruct the final result via CRT.

def chinese_remainder_theorem(remainders: list[int], moduli: list[int]) -> int:
    """Solves x ≡ r_i (mod m_i) for pairwise coprime moduli."""
    M = 1
    for m in moduli:
        M *= m
    total = 0
    for r_i, m_i in zip(remainders, moduli):
        M_i = M // m_i
        y_i = mod_inverse(M_i, m_i)
        total = (total + r_i * M_i * y_i) % M
    return total

print("CRT([2, 3, 2], [3, 5, 7]) =", chinese_remainder_theorem([2, 3, 2], [3, 5, 7]))  # 23


10. Fast Modular Exponentiation (Binary Exponentiation / Exponentiation by Squaring)

Computing $b^e \bmod m$ is the core bottleneck of RSA and Diffie-Hellman.

Naive Powering: Computing $b^e$ first and then taking $\bmod m$ creates an integer with $e \log_{10}(b)$ digits—impossible when $e \approx 2^{2048}$.

Repeated Multiplication: Looping $e$ times multiplying by $b \pmod m$ takes $O(e)$ steps—still impossible for 2048-bit exponents.

Binary Squaring Algorithm ($O(\log e)$)

Write $e$ in binary: $e = \sum_{i=0}^k b_i 2^i$ where $b_i \in \{0, 1\}$. Then:


$$b^e = \prod_{b_i = 1} b^{2^i} \pmod{m}$$


We compute the sequence $b^{2^0}, b^{2^1}, b^{2^2}, \dots, b^{2^k} \pmod{m}$ by repeated squaring ($k = \lfloor \log_2 e \rfloor$ multiplications) and multiply together the terms where $b_i = 1$ (at most $k$ multiplications). Total multiplications: $\le 2 \log_2 e$.

Worked Example: Compute $7^{13} \bmod 11$. Since $13 = 1101_2 = 8 + 4 + 1$:

$7^1 \equiv 7 \pmod{11}$  (Include: bit 0 is 1)

$7^2 \equiv 49 \equiv 5 \pmod{11}$  (Skip: bit 1 is 0)

$7^4 \equiv 5^2 = 25 \equiv 3 \pmod{11}$  (Include: bit 2 is 1)

$7^8 \equiv 3^2 = 9 \pmod{11}$  (Include: bit 3 is 1)

Result: $7^{13} \equiv 7 \times 3 \times 9 = 189 \equiv 2 \pmod{11}$.

def fast_mod_exp(b: int, e: int, m: int) -> int:
    """Computes (b^e) mod m using at most 2*log2(e) modular multiplications."""
    if m == 1:
        return 0
    result = 1
    b %= m
    while e > 0:
        if e & 1:
            result = (result * b) % m
        b = (b * b) % m
        e >>= 1
    return result

print("7^13 mod 11 =", fast_mod_exp(7, 13, 11))  # 2


11. Fermat's Little Theorem (FLT): Cycle Graph Proof & Optimization

Theorem Statement

If $p$ is a prime number and $a$ is an integer not divisible by $p$ ($p \nmid a$), then:


$$a^{p-1} \equiv 1 \pmod{p}$$


Equivalently, for every integer $a \in \mathbb{Z}$:


$$a^p \equiv a \pmod{p}$$

Cycle Graph Proof

Consider the $p - 1$ non-zero residues $\{1, 2, \dots, p - 1\}$ modulo $p$.

Construct a directed graph where each vertex $r$ has a single outgoing edge to $(a \cdot r) \bmod p$.

Because $\gcd(a, p) = 1$, multiplication by $a$ is invertible modulo $p$, so every vertex also has in-degree $1$.

Thus, the graph decomposes into disjoint directed cycles of equal length $l$ (the multiplicative order $\text{ord}_p(a)$), where $a^l \equiv 1 \pmod{p}$.

If there are $c$ cycles, then $c \cdot l = p - 1$, giving:


$$a^{p-1} = a^{cl} = (a^l)^c \equiv 1^c \equiv 1 \pmod{p} \quad \blacksquare$$

Exponent Reduction Optimization

For prime $p$ and $p \nmid a$:


$$a^n \equiv a^{n \bmod (p - 1)} \pmod{p}$$

12. Euler's Totient Function $\phi(n)$ & Euler's Generalization Theorem

Euler's Totient Function $\phi(n)$

$\phi(n)$ counts the number of positive integers $k \in \{1, 2, \dots, n\}$ such that $\gcd(k, n) = 1$.

Prime Argument: $\phi(p) = p - 1$.

Prime Power: $\phi(p^k) = p^k - p^{k-1} = p^k\left(1 - \frac{1}{p}\right)$.

Product of Two Primes ($n = pq$): By CRT, a residue $r \pmod{pq}$ is coprime to $pq$ iff $r \bmod p \neq 0$ and $r \bmod q \neq 0$, leaving $(p - 1)(q - 1)$ valid pairs:


$$\phi(pq) = (p - 1)(q - 1)$$

General Product Formula: For $n = \prod_{i=1}^r p_i^{a_i}$:


$$\phi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right)$$

Euler's Theorem

If $\gcd(a, n) = 1$, then:


$$a^{\phi(n)} \equiv 1 \pmod{n}$$


(Notice that when $n = p$ is prime, $\phi(p) = p - 1$, reducing immediately to Fermat's Little Theorem.)

def euler_totient(n: int) -> int:
    """Computes phi(n) in O(sqrt(n)) time."""
    result = n
    p = 2
    temp = n
    while p * p <= temp:
        if temp % p == 0:
            while temp % p == 0:
                temp //= p
            result -= result // p
        p += 1
    if temp > 1:
        result -= result // temp
    return result

print("phi(3233) [where 3233 = 61 * 53] =", euler_totient(3233))  # 3120


13. Prime Numbers: Eight Classic Proofs of Infinitude

A prime number is an integer $p > 1$ that cannot be written as a product of two smaller positive integers. By the Fundamental Theorem of Arithmetic, every integer $n > 1$ has a unique prime factorization $n = p_1^{a_1} p_2^{a_2} \cdots p_k^{a_k}$.

Here are 8 distinct proofs that there are infinitely many primes:

Euclid's Proof ($\prod p_i + 1$): Suppose $p_1, \dots, p_k$ are all primes. Consider $N = p_1 p_2 \cdots p_k + 1 > 1$. Any prime divisor $q$ of $N$ cannot be any $p_i$, else $q \mid (N - p_1 \cdots p_k) = 1$, a contradiction.

Factorial Proof ($n! + 1$): For any $n \ge 1$, $n! + 1$ has a prime factor strictly greater than $n$ (since every $2 \le k \le n$ divides $n!$).

Euler's Analytic Proof (Harmonic Series): If there were finitely many primes, the finite Euler product $\prod_p \frac{1}{1 - 1/p}$ would bound partial sums of the harmonic series $H_n = \sum_{m=1}^n \frac{1}{m}$, contradicting the divergence of $\sum_{m=1}^\infty \frac{1}{m}$.

Goldbach's Proof (Fermat Numbers): Fermat numbers $F_n = 2^{2^n} + 1$ satisfy $F_m - 2 = F_0 F_1 \cdots F_{m-1}$. Since every $F_n$ is odd, $\gcd(F_n, F_m) = 1$ for $n < m$. Picking one prime factor from each $F_n$ gives infinitely many distinct primes.

Filip Saidak's Constructive Proof: Start with any $n > 1$. Since $n$ and $n+1$ are coprime, $N_2 = n(n+1)$ has $\ge 2$ prime factors. Since $N_2$ and $N_2 + 1$ are coprime, $N_3 = N_2(N_2 + 1)$ has $\ge 3$ prime factors. Repeating produces numbers with arbitrarily many distinct prime factors.

Furstenberg's Topological Proof: Define a topology on $\mathbb{Z}$ generated by arithmetic progressions $S(a, b) = \{an + b\}$. Every basis set is both open and closed. Since $\mathbb{Z} \setminus \{-1, 1\} = \bigcup_{p \text{ prime}} S(p, 0)$, finitely many primes would imply $\{-1, 1\}$ is open—impossible since every non-empty open set is infinite.

Primes of the Form $4k + 1$: Consider $N = (2 p_1 p_2 \cdots p_k)^2 + 1$. Every odd prime factor $q \mid N$ satisfies $-1 \equiv x^2 \pmod{q}$, which by Euler's Criterion requires $q \equiv 1 \pmod{4}$.

Primes of the Form $4k + 3$: Consider $N = 4 p_1 p_2 \cdots p_k - 1 \equiv 3 \pmod{4}$. Since a product of numbers $\equiv 1 \pmod{4}$ is $\equiv 1 \pmod{4}$, $N$ must have at least one prime factor $q \equiv 3 \pmod{4}$ not in $\{p_1, \dots, p_k\}$.

14. Distribution of Primes, Prime Number Theorem & Famous Conjectures

Dirichlet's Theorem on Arithmetic Progressions: Given positive integers $a, b$ with $\gcd(a, b) = 1$, there are infinitely many primes of the form $ak + b$. (Proved using Dirichlet $L$-series and Analytic Number Theory.)

Prime Number Theorem (PNT): Let $\pi(x)$ count the primes $\le x$. Asymptotically:


$$\pi(x) \sim \frac{x}{\ln x} \quad \text{as } x \to \infty$$


Equivalently, the density of primes near $x$ is approximately $\frac{1}{\ln x}$.

Polynomials & Matiyasevich's Theorem: Euler's quadratic $n^2 + n + 41$ yields primes for $0 \le n \le 39$, but fails at $n = 40$ ($41^2$) and $n = 41$ ($41 \times 43$). No single-variable non-constant polynomial generates only primes, though Yuri Matiyasevich proved there exists a polynomial in 10 variables whose positive values are precisely the set of all primes!

Open & Famous Conjectures:

Goldbach's Conjecture: Every even integer $> 2$ is the sum of two primes. (Chen's Theorem proved every sufficiently large even integer is $p_1 + p_2$ or $p_1 + p_2 p_3$.)

Waring's Prime Conjecture (Ternary Goldbach): Every odd integer $> 5$ is the sum of three primes (proved by Harald Helfgott in 2013).

Twin Prime Conjecture: Infinitely many primes $p$ such that $p + 2$ is prime.

Legendre's Conjecture: There is always at least one prime between $n^2$ and $(n+1)^2$.

Landau's Problem: Infinitely many primes of the form $n^2 + 1$.

15. Primality Testing, Sieve of Eratosthenes, Wheel Factorization & Lucas's Theorem

1. Sieve of Eratosthenes & Wheel Factorization

Sieve of Eratosthenes: Marks multiples of each prime $p \le \sqrt{n}$ in $O(n \log \log n)$ time.

Wheel of 30 Optimization: Since $2 \times 3 \times 5 = 30$, any prime $> 5$ must be congruent modulo $30$ to one of the $\phi(30) = 8$ coprime residues:


$$\{1, 7, 11, 13, 17, 19, 23, 29\} \pmod{30}$$


This skips $\frac{22}{30} \approx 73.33\%$ of all integers before performing a single division!

2. Lucas's Primality Theorem & Pocklington's $n - 1$ Test

Lucas's Theorem: An integer $n > 1$ is prime if for every prime factor $q$ of $n - 1$, there exists an integer $a$ such that:


$$a^{n-1} \equiv 1 \pmod{n} \quad \text{and} \quad a^{(n-1)/q} \not\equiv 1 \pmod{n}$$


(This proves $\text{ord}_n(a) = n - 1$, forcing $\phi(n) = n - 1$, so $n$ is prime.)

Pocklington's $n - 1$ Test: Requires factoring only a part $F$ of $n - 1 = F \cdot R$ where $F > R$ and $\gcd(F, R) = 1$.

def wheel_30_candidates(limit: int) -> list[int]:
    """Generates primality test candidates up to `limit` using a Mod-30 Wheel."""
    base_primes = [p for p in [2, 3, 5] if p <= limit]
    spokes = [1, 7, 11, 13, 17, 19, 23, 29]
    candidates = []
    k = 0
    while True:
        added = False
        for s in spokes:
            val = 30 * k + s
            if 5 < val <= limit:
                candidates.append(val)
                added = True
            elif val > limit:
                return base_primes + candidates
        k += 1

print("Mod-30 Wheel candidates <= 60:", wheel_30_candidates(60))


16. Fermat Pseudoprimes, Carmichael Numbers & Korselt's Criterion

Fermat Pseudoprimes

By Fermat's Little Theorem, if $n$ is prime and $\gcd(a, n) = 1$, then $a^{n-1} \equiv 1 \pmod{n}$.

If $a^{n-1} \not\equiv 1 \pmod{n}$, $n$ is guaranteed composite ($a$ is a Fermat witness).

However, the converse is false:

$341 = 11 \times 31$ is composite, yet $2^{340} \equiv 1 \pmod{341}$ (a Fermat pseudoprime to base 2). Testing base $a = 3$ catches it: $3^{340} \equiv 56 \not\equiv 1 \pmod{341}$.

$91 = 7 \times 13$ is a pseudoprime to base $3$, but caught by base $2$.

Carmichael Numbers (Absolute Pseudoprimes)

A Carmichael number is a composite integer $n$ such that:


$$a^{n-1} \equiv 1 \pmod{n} \quad \text{for ALL } a \text{ with } \gcd(a, n) = 1$$


Thus, Carmichael numbers fool Fermat's test for every coprime base!

First Five Carmichael Numbers: $561, \; 1105, \; 1729, \; 2465, \; 2821$.

Korselt's Criterion (1899): A positive composite integer $n$ is a Carmichael number if and only if:

$n$ is square-free ($p^2 \nmid n$ for all primes $p$), AND

$(p - 1) \mid (n - 1)$ for every prime divisor $p \mid n$.

Verification for $561 = 3 \times 11 \times 17$: Square-free, and $2 \mid 560$, $10 \mid 560$, $16 \mid 560$.

17. Special Primes: Mersenne Primes, Lucas-Lehmer Test, Perfect Numbers & Antiprimes

1. Mersenne Primes & The Lucas-Lehmer Test

Mersenne Numbers: $M_n = 2^n - 1$. If $M_n$ is prime, then $n$ itself must be prime (since $2^{ab} - 1 = (2^a - 1)(1 + 2^a + \dots + 2^{a(b-1)})$). However, $p$ being prime does not guarantee $M_p$ is prime (e.g., $M_{11} = 2047 = 23 \times 89$).

Small Mersenne Prime Exponents: $p \in \{2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127\}$.

Lucas-Lehmer Primality Test: Define the sequence $s_0 = 4$ and $s_k = s_{k-1}^2 - 2$. For an odd prime $p$:


$$M_p = 2^p - 1 \text{ is prime} \iff s_{p-2} \equiv 0 \pmod{M_p}$$


In 1876, Édouard Lucas used this test to prove $M_{127} = 2^{127} - 1$ (a 39-digit number) is prime—the largest prime ever proven by hand!

2. Perfect Numbers & Euclid-Euler Theorem

A positive integer $n$ is perfect if the sum of its proper divisors equals $n$ ($\sigma(n) = 2n$).

First four perfect numbers:


$$6 = 2^1(2^2 - 1), \quad 28 = 2^2(2^3 - 1), \quad 496 = 2^4(2^5 - 1), \quad 8128 = 2^6(2^7 - 1)$$

Euclid-Euler Theorem: An even integer $n$ is perfect if and only if $n = 2^{p-1}(2^p - 1)$ where $2^p - 1$ is a Mersenne prime.

3. Antiprimes (Highly Composite Numbers)

An antiprime (coined by Srinivasa Ramanujan) is a positive integer $n$ that has strictly more divisors $d(n) = \prod_{i=1}^k (a_i + 1)$ than any smaller positive integer $m < n$.

Examples: $1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360$.

Structural Properties: Its prime factorization $n = 2^{a_1} 3^{a_2} \cdots p_k^{a_k}$ uses consecutive primes starting at $2$, with non-increasing exponents $a_1 \ge a_2 \ge \dots \ge a_k \ge 1$ (and $a_k = 1$ for all $n > 36$).

def lucas_lehmer_test(p: int) -> bool:
    """Tests if Mersenne number M_p = 2^p - 1 is prime for prime p."""
    if p == 2:
        return True
    M_p = (1 << p) - 1
    s = 4
    for _ in range(p - 2):
        s = (s * s - 2) % M_p
    return s == 0

print("Lucas-Lehmer M_127 (2^127 - 1):", lucas_lehmer_test(127))  # True


18. Cryptographic Synthesis: Symmetric vs. Asymmetric Encryption & Full RSA Implementation

Symmetric vs. Public-Key (Asymmetric) Cryptography

Symmetric Ciphers (e.g., Caesar, Enigma, AES): Both parties share the same secret key. Reusing static codes leaks statistical patterns, and sharing a fresh key across continents without an eavesdropper (Mallory) intercepting it is the Key Distribution Problem.

Public-Key Cryptography (RSA): Solves key distribution using a trapdoor one-way function—multiplying two large primes $p \times q = n$ is fast ($O(\log^2 n)$), while factoring $n$ back into $p$ and $q$ (to compute $\phi(n) = (p-1)(q-1)$) is computationally intractable.

Mathematical Correctness of RSA

Key Setup: Choose distinct primes $p, q$. Set $n = pq$ and $\phi(n) = (p - 1)(q - 1)$. Choose $e$ with $\gcd(e, \phi(n)) = 1$, and compute $d \equiv e^{-1} \pmod{\phi(n)}$ so that $ed = 1 + k\phi(n)$.

Encryption: $c = m^e \bmod n$.

Decryption: Using Euler's Theorem ($m^{\phi(n)} \equiv 1 \pmod{n}$):


$$c^d \equiv (m^e)^d = m^{ed} = m^{1 + k\phi(n)} = m \cdot (m^{\phi(n)})^k \equiv m \cdot 1^k \equiv m \pmod{n}$$

def rsa_demo(p: int, q: int, e: int, plaintext: str):
    """Full string-to-integer RSA encryption and decryption pipeline."""
    n = p * q
    phi_n = (p - 1) * (q - 1)
    d = mod_inverse(e, phi_n)
    
    # Encrypt each character ASCII value
    cipher_blocks = [fast_mod_exp(ord(ch), e, n) for ch in plaintext]
    # Decrypt each ciphertext block
    decrypted_chars = [chr(fast_mod_exp(c, d, n)) for c in cipher_blocks]
    return n, d, cipher_blocks, "".join(decrypted_chars)

n, d, cipher, recovered = rsa_demo(61, 53, 17, "NUMBER THEORY")
print(f"RSA Public (n={n}, e=17) | Private d={d}")
print("Ciphertext:", cipher)
print("Decrypted :", recovered)


End of Study Guide & Repository Documentation.
