# Number Theory and Cryptography

**Student Name:** Abdur Rahim  
**Student ID:** IT22053  
**Course/Topic:** Number Theory and Cryptography

---

## Overview

This repository contains study notes, Python implementations, worked examples, and practical exercises based on the two supplied lecture resources:

- **Day 1.pdf** — Number theory foundations, modular arithmetic, GCD/LCM, Diophantine equations, the Chinese Remainder Theorem, modular exponentiation, Fermat's Little Theorem, Euler's totient function, and Euler's theorem.
- **Day 2.pdf** — Prime numbers, prime distribution and conjectures, primality testing, pseudoprimes, Carmichael numbers, Lucas tests, Mersenne primes, perfect numbers, and antiprimes.

The notebooks are designed to run in **Google Colab** or **Jupyter Notebook**.

## Repository structure

```text
Number_Theory_Cryptography_IT22053/
├── README.md
├── requirements.txt
├── notebooks/
│   ├── Day_1_Number_Theory.ipynb
│   └── Day_2_Prime_Numbers.ipynb
└── figures/
    └── prime_sieve_example.png
```

## Learning outcomes

After working through the material, a learner should be able to:

1. Compute GCD and LCM efficiently.
2. Use the Extended Euclidean Algorithm to find Bézout coefficients and modular inverses.
3. Solve linear Diophantine equations when integer solutions exist.
4. Perform modular arithmetic and solve systems using the Chinese Remainder Theorem.
5. Compute large modular powers efficiently.
6. Apply Fermat's Little Theorem and Euler's theorem.
7. Calculate Euler's totient function for factored integers.
8. Generate primes with the Sieve of Eratosthenes and test small integers for primality.
9. Explain why Fermat tests can be fooled by pseudoprimes and Carmichael numbers.
10. Explore Mersenne primes, perfect numbers, and divisor-counting functions.

---

# Day 1 — Number Theory and Cryptography

## 1. Greatest Common Divisor (GCD)

The greatest common divisor of two integers is the largest positive integer that divides both.

\[
\gcd(24,16)=8,\qquad \gcd(9,17)=1
\]

### Euclid's Algorithm

For \(a\ge b>0\),

\[
\gcd(a,b)=\gcd(b,a\bmod b)
\]

Repeat the replacement until the remainder is zero. The last non-zero remainder is the GCD.

**Example**

\[
\begin{aligned}
24 &= 1(16)+8\\
16 &= 2(8)+0
\end{aligned}
\qquad \therefore \gcd(24,16)=8
\]

## 2. Extended Euclidean Algorithm

It finds integers \(x,y\) such that

\[
ax+by=\gcd(a,b).
\]

For example,

\[
2=10(-1)+6(2).
\]

This identity is useful for finding modular inverses.

## 3. Least Common Multiple (LCM)

For positive integers \(a,b\),

\[
\operatorname{lcm}(a,b)=\frac{ab}{\gcd(a,b)}.
\]

For example, \(\operatorname{lcm}(24,16)=48\).

## 4. Linear Diophantine Equations

A linear Diophantine equation has the form

\[
ax+by=c
\]

where integer solutions are required. It has an integer solution **if and only if**

\[
\gcd(a,b)\mid c.
\]

If \((x_0,y_0)\) is one solution and \(d=\gcd(a,b)\), then all integer solutions are

\[
x=x_0+t\frac{b}{d},\qquad
y=y_0-t\frac{a}{d},\qquad t\in\mathbb Z.
\]

## 5. Modular Arithmetic and Modular Inverses

\[
a\equiv b\pmod n
\]

means that \(n\) divides \(a-b\). A modular inverse of \(a\) modulo \(n\) is an integer \(a^{-1}\) satisfying

\[
aa^{-1}\equiv1\pmod n.
\]

An inverse exists exactly when \(\gcd(a,n)=1\).

Example: \(2^{-1}\equiv5\pmod9\), because \(2\cdot5=10\equiv1\pmod9\).

## 6. Chinese Remainder Theorem (CRT)

If \(m,n\) are coprime, the pair of congruences

\[
x\equiv a\pmod m,\qquad x\equiv b\pmod n
\]

has a unique solution modulo \(mn\).

Example:

\[
x\equiv2\pmod3,\qquad x\equiv3\pmod5
\]

gives \(x\equiv8\pmod{15}\).

## 7. Fast Modular Exponentiation

Compute \(b^e\bmod m\) without constructing the very large integer \(b^e\). Repeated squaring reduces the number of multiplications to logarithmic order in \(e\).

\[
b^e\bmod m
\]

Python also provides `pow(b, e, m)` for efficient modular exponentiation.

## 8. Fermat's Little Theorem

If \(p\) is prime, then

\[
a^p\equiv a\pmod p.
\]

If \(p\nmid a\), this is equivalent to

\[
a^{p-1}\equiv1\pmod p.
\]

The converse is not always true; composite numbers can pass a Fermat test for particular bases.

## 9. Euler's Totient Function

\(\phi(n)\) counts the integers from \(1\) to \(n\) that are coprime to \(n\).

For prime \(p\),

\[
\phi(p)=p-1.
\]

For distinct primes \(p,q\),

\[
\phi(pq)=(p-1)(q-1).
\]

More generally, if \(n=\prod p_i^{a_i}\),

\[
\phi(n)=n\prod_{p\mid n}\left(1-\frac1p\right).
\]

## 10. Euler's Theorem

If \(\gcd(a,n)=1\), then

\[
a^{\phi(n)}\equiv1\pmod n.
\]

This generalizes Fermat's Little Theorem and is one of the mathematical foundations used in the RSA construction.

---

# Day 2 — Prime Numbers

## 1. Prime Numbers

A prime is a natural number greater than \(1\) whose only positive divisors are \(1\) and itself. Examples: \(2,3,5,7,11,13\).

The Fundamental Theorem of Arithmetic states that every integer greater than \(1\) has a unique prime factorization, apart from the order of the factors.

## 2. Infinitely Many Primes

Euclid's classic argument assumes a finite list of primes \(p_1,\ldots,p_k\) and considers

\[
N=p_1p_2\cdots p_k+1.
\]

No listed prime divides \(N\), so a prime factor outside the list must exist. Therefore there cannot be only finitely many primes.

The lecture also introduces other approaches to the infinitude of primes, including harmonic-series, Goldbach, Saidak, and topology-related arguments.

## 3. Prime Distribution and Prime Number Theorem

Let \(\pi(x)\) count primes not exceeding \(x\). The Prime Number Theorem states asymptotically that

\[
\pi(x)\sim\frac{x}{\ln x}.
\]

This describes the approximate density of primes among large positive integers.

## 4. Prime Conjectures

The lecture discusses the Goldbach conjecture, twin-prime conjecture, prime patterns, prime spirals, and related questions. These are conjectures unless a proof is known; computational examples alone do not establish them.

## 5. Sieve of Eratosthenes

To find all primes up to \(n\):

1. List integers from \(2\) through \(n\).
2. Starting with \(2\), cross out its multiples.
3. Continue with each next number not crossed out.
4. Stop after processing primes up to \(\sqrt n\).
5. The remaining numbers are prime.

![Sieve of Eratosthenes example](figures/prime_sieve_example.png)

## 6. Trial Division

To test a candidate \(n\), it is enough to check possible divisors up to \(\sqrt n\). If a composite number \(n=ab\) has both factors greater than \(\sqrt n\), their product would exceed \(n\), which is impossible.

## 7. Fermat Primality Test and Pseudoprimes

For a candidate \(n>1\), choose a base \(a\) coprime to \(n\). If

\[
a^{n-1}\not\equiv1\pmod n,
\]

then \(n\) is composite. If the congruence holds, the test is inconclusive: \(n\) may be prime or a pseudoprime to that base.

The lecture gives examples: 341 is a base-2 pseudoprime but not a base-3 pseudoprime; 91 is a base-3 pseudoprime but not a base-2 pseudoprime.

## 8. Carmichael Numbers

A Carmichael number is a composite positive integer \(n\) satisfying

\[
a^n\equiv a\pmod n
\]

for every integer \(a\). The first examples include \(561,1105,1729,2465,2821\). Thus, a Fermat-style test cannot prove primality merely because a candidate passes one or even many bases.

## 9. Lucas Primality Test

The lecture presents Lucas's theorem: for \(n>1\), if for every prime factor \(q\) of \(n-1\) there is an integer \(a\) such that

\[
a^{n-1}\equiv1\pmod n
\]

and

\[
a^{(n-1)/q}\not\equiv1\pmod n,
\]

then \(n\) is prime.

## 10. Mersenne Primes and Perfect Numbers

A Mersenne number has the form

\[
M_p=2^p-1.
\]

If \(M_p\) is prime, it is called a Mersenne prime. A perfect number equals the sum of its positive divisors excluding itself. Examples are \(6,28,496,8128\).

## 11. Number of Divisors and Antiprimes

If the prime factorization is

\[
n=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k},
\]

then the number of positive divisors is

\[
d(n)=\prod_{i=1}^{k}(a_i+1).
\]

An antiprime (highly composite number) has more positive divisors than every smaller positive integer.

---

# Practical work

Open the notebooks in `notebooks/` and run every cell in order.

| Notebook | Practical activities |
|---|---|
| `Day_1_Number_Theory.ipynb` | GCD, Extended GCD, LCM, modular inverse, Diophantine equation, CRT, modular exponentiation, totient, Fermat and Euler checks, toy RSA demonstration |
| `Day_2_Prime_Numbers.ipynb` | Sieve, trial division, prime distribution, Fermat test, pseudoprimes, Carmichael examples, Mersenne numbers, perfect numbers, divisor counting |

## Run in Google Colab

1. Download this repository ZIP and extract it.
2. Open [Google Colab](https://colab.research.google.com/).
3. Choose **File → Upload notebook**.
4. Upload a notebook from the `notebooks` folder.
5. Run cells from top to bottom using **Runtime → Run all**.
6. Review the output and complete the exercises in the final section of each notebook.

## Run locally with Jupyter

```bash
python -m pip install -r requirements.txt
jupyter notebook
```

## Important learning and security notes

- The RSA example in the Day 1 notebook uses tiny educational primes. It is for learning only and is **not secure for real communication**.
- A Fermat test is a probable-prime check, not a proof of primality.
- The notebooks distinguish proved theorems from conjectures.
- Run the examples yourself and add your own observations before submission.

## References

1. **Day 1.pdf** — Course-provided lecture resource on Number Theory and Cryptography.
2. **Day 2.pdf** — *Prime Numbers*, Maths and Physics Club, IIT Bombay, December 24, 2020.
3. Python documentation: https://docs.python.org/3/library/functions.html#pow
4. Google Colab: https://colab.research.google.com/

---


