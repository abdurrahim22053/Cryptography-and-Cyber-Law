# Number Theory, Cryptography & Prime Numbers

                                          Name: Abdur Rahim  
                                          Student ID: IT22053  
Course/Workshop: Number Theory and Cryptography  


---

## Table of Contents

> GitHub automatically turns these headings into links. Click a topic to jump to it.

- [1. Introduction to Number Theory](#1-introduction-to-number-theory)
- [2. Divisibility, Factors and Multiples](#2-divisibility-factors-and-multiples)
- [3. Greatest Common Divisor (GCD)](#3-greatest-common-divisor-gcd)
  - [3.1 Naive GCD Algorithm](#31-naive-gcd-algorithm)
  - [3.2 Euclid's Lemma and Subtraction Algorithm](#32-euclids-lemma-and-subtraction-algorithm)
  - [3.3 Euclid's Algorithm](#33-euclids-algorithm)
  - [3.4 Extended Euclidean Algorithm and Bézout's Identity](#34-extended-euclidean-algorithm-and-bézouts-identity)
- [4. Least Common Multiple (LCM)](#4-least-common-multiple-lcm)
- [5. Diophantine Equations](#5-diophantine-equations)
  - [5.1 Existence of Integer Solutions](#51-existence-of-integer-solutions)
  - [5.2 Finding All Solutions](#52-finding-all-solutions)
- [6. Modular Arithmetic and Remainders](#6-modular-arithmetic-and-remainders)
  - [6.1 Congruence Properties](#61-congruence-properties)
  - [6.2 Divisibility Criteria](#62-divisibility-criteria)
- [7. Modular Multiplicative Inverse and Division](#7-modular-multiplicative-inverse-and-division)
- [8. Chinese Remainder Theorem (CRT)](#8-chinese-remainder-theorem-crt)
- [9. Fast Modular Exponentiation](#9-fast-modular-exponentiation)
- [10. Fermat's Little Theorem](#10-fermats-little-theorem)
- [11. Euler's Totient Function](#11-eulers-totient-function)
- [12. Euler's Theorem](#12-eulers-theorem)
- [13. Cryptography and Public-Key Idea](#13-cryptography-and-public-key-idea)
- [14. Prime Numbers](#14-prime-numbers)
  - [14.1 Prime Distribution and Infinitude](#141-prime-distribution-and-infinitude)
  - [14.2 Dirichlet's Theorem and Prime Number Theorem](#142-dirichlets-theorem-and-prime-number-theorem)
  - [14.3 Prime Conjectures](#143-prime-conjectures)
  - [14.4 Generating Primes and Polynomial Examples](#144-generating-primes-and-polynomial-examples)
- [15. Primality Testing](#15-primality-testing)
  - [15.1 Trial Division](#151-trial-division)
  - [15.2 Sieve of Eratosthenes](#152-sieve-of-eratosthenes)
  - [15.3 Wheel Factorization](#153-wheel-factorization)
  - [15.4 Pseudoprimes and Fermat Primality Test](#154-pseudoprimes-and-fermat-primality-test)
  - [15.5 Carmichael Numbers](#155-carmichael-numbers)
  - [15.6 Lucas' Primality Test and the n-1 Test](#156-lucas-primality-test-and-the-n-1-test)
  - [15.7 Lucas-Lehmer Test and Mersenne Primes](#157-lucas-lehmer-test-and-mersenne-primes)
- [16. Further Properties of Prime Numbers](#16-further-properties-of-prime-numbers)
  - [16.1 Primitive Roots and Multiplicative Order](#161-primitive-roots-and-multiplicative-order)
  - [16.2 Prime Characterizations](#162-prime-characterizations)
- [17. Divisor Functions and Antiprimes](#17-divisor-functions-and-antiprimes)
- [18. Fundamental Theorem of Arithmetic](#18-fundamental-theorem-of-arithmetic)
- [19. Practice Problems](#19-practice-problems)
- [20. References and Scope Notes](#20-references-and-scope-notes)

---

## 1. Introduction to Number Theory

Number theory is the branch of mathematics that studies integers and their properties. It investigates divisibility, prime numbers, greatest common divisors, remainders, congruences, and integer equations.

These ideas are important in computer science because algorithms often need to work with integers efficiently. Number theory is also a mathematical foundation of public-key cryptography.

### Main types of numbers

| Type | Meaning | Examples |
|---|---|---|
| Natural numbers | Counting numbers (convention may start at 1) | 1, 2, 3, ... |
| Integers | Positive, negative and zero | -3, -2, -1, 0, 1, ... |
| Even integers | Integers divisible by 2 | -4, 0, 6 |
| Odd integers | Integers not divisible by 2 | -3, 1, 7 |
| Prime numbers | Integers greater than 1 with exactly two positive divisors | 2, 3, 5, 7 |
| Composite numbers | Integers greater than 1 with more than two positive divisors | 4, 6, 8, 9 |

### Python: basic integer properties

```python
# Check basic properties of an integer.
n = 29

print("Number:", n)
print("Even:", n % 2 == 0)
print("Odd:", n % 2 != 0)
print("Square:", n ** 2)
```

**Expected output**
```text
Number: 29
Even: False
Odd: True
Square: 841
```

---

## 2. Divisibility, Factors and Multiples

For integers `a` and `b`, with `a != 0`, we say that `a` divides `b` if there is an integer `k` such that:

\[
b = ak
\]

The notation is:

\[
a \mid b
\]

If no such integer `k` exists, we write \(a \nmid b\).

- A **factor/divisor** divides a number exactly.
- A **multiple** is obtained by multiplying a number by an integer.
- Example: \(4 \mid 20\), because \(20 = 4 \times 5\).
- Example: \(6 \nmid 20\), because 20 is not divisible by 6 without a remainder.

### Python: list the positive divisors

```python
# Return every positive divisor of n.
def divisors(n):
    if n <= 0:
        raise ValueError("Enter a positive integer.")

    result = []
    for d in range(1, n + 1):
        if n % d == 0:
            result.append(d)
    return result

print(divisors(24))
```

**Expected output**
```text
[1, 2, 3, 4, 6, 8, 12, 24]
```

---

## 3. Greatest Common Divisor (GCD)

The **greatest common divisor** of two integers (not both zero) is the largest positive integer that divides both numbers.

It is written as:

\[
\gcd(a,b)
\]

Examples:

\[
\gcd(24,16)=8,\quad \gcd(9,17)=1,\quad \gcd(239,0)=239
\]

Two integers are called **coprime** or **relatively prime** when their GCD is 1.

### 3.1 Naive GCD Algorithm

The direct method checks possible divisors from the smaller input down to 1. The first number that divides both inputs is the GCD.

This method is easy to understand, but it can be slow for large numbers. In a worst-case coprime input, it may test almost every integer up to the smaller input.

```python
# A simple GCD algorithm that checks candidate divisors one by one.
def gcd_naive(a, b):
    a, b = abs(a), abs(b)

    if a == 0 and b == 0:
        raise ValueError("GCD is undefined for gcd(0, 0).")

    for candidate in range(min(a, b), 0, -1):
        if a % candidate == 0 and b % candidate == 0:
            return candidate

    return max(a, b)

print(gcd_naive(24, 16))
print(gcd_naive(9, 17))
```

**Expected output**
```text
8
1
```

### 3.2 Euclid's Lemma and Subtraction Algorithm

A useful form of Euclid's lemma is:

\[
d\mid a \text{ and } d\mid b
\iff d\mid(a-b) \text{ and } d\mid b
\]

Therefore:

\[
\gcd(a,b)=\gcd(a-b,b), \quad a\ge b>0
\]

Repeated subtraction eventually finds the GCD. However, if one number is very large and the other is small, subtraction may repeat many times.

```python
# GCD using repeated subtraction; useful for understanding the idea.
def gcd_subtraction(a, b):
    a, b = abs(a), abs(b)

    if a == 0 and b == 0:
        raise ValueError("GCD is undefined for gcd(0, 0).")

    while a != 0 and b != 0:
        if a >= b:
            a -= b
        else:
            b -= a

    return max(a, b)

print(gcd_subtraction(10, 6))
```

**Expected output**
```text
2
```

### 3.3 Euclid's Algorithm

Euclid's algorithm improves repeated subtraction by using the remainder operation.

The key identity is:

\[
\gcd(a,b)=\gcd(b,a\bmod b)
\]

The process continues until the remainder becomes zero. The last non-zero remainder is the GCD.

Example:

\[
\begin{aligned}
24 &= 1(16)+8\\
16 &= 2(8)+0
\end{aligned}
\]

Therefore, \(\gcd(24,16)=8\).

```python
# Efficient iterative Euclidean algorithm.
def gcd_euclid(a, b):
    a, b = abs(a), abs(b)

    if a == 0 and b == 0:
        raise ValueError("GCD is undefined for gcd(0, 0).")

    while b != 0:
        a, b = b, a % b  # Replace (a, b) with (b, remainder).

    return a

print(gcd_euclid(24, 16))
print(gcd_euclid(790933790547, 1849639579327))
```

**Expected output**
```text
8
3416723
```

The Euclidean algorithm is efficient: the number of iterations grows logarithmically with the size of the inputs. The workshop notes give a bound of at most \(\log_2 a+\log_2 b\) iterations for positive inputs.

### 3.4 Extended Euclidean Algorithm and Bézout's Identity

The extended Euclidean algorithm finds integers \(x\) and \(y\) such that:

\[
ax+by=\gcd(a,b)
\]

This is called **Bézout's identity**.

For example:

\[
\gcd(10,6)=2=10(-1)+6(2)
\]

The coefficients are useful for finding modular inverses and solving linear Diophantine equations.

```python
# Return (g, x, y), where a*x + b*y = g = gcd(a, b).
def extended_gcd(a, b):
    if b == 0:
        # Base case: gcd(a, 0) = abs(a).
        return abs(a), 1 if a >= 0 else -1, 0

    g, x1, y1 = extended_gcd(b, a % b)

    # Back-substitute the coefficients from the recursive call.
    x = y1
    y = x1 - (a // b) * y1
    return g, x, y

g, x, y = extended_gcd(10, 6)
print("GCD:", g)
print("x:", x)
print("y:", y)
print("Verification:", 10*x + 6*y)
```

**Expected output**
```text
GCD: 2
x: -1
y: 2
Verification: 2
```

---

## 4. Least Common Multiple (LCM)

The **least common multiple** of two positive integers is the smallest positive integer divisible by both.

\[
\operatorname{lcm}(a,b)
\]

An important relationship is:

\[
\operatorname{lcm}(a,b)\times\gcd(a,b)=|ab|
\]

For positive \(a,b\):

\[
\operatorname{lcm}(a,b)=\frac{ab}{\gcd(a,b)}
\]

Example:

\[
\operatorname{lcm}(24,16)=\frac{24\times16}{8}=48
\]

```python
# Calculate LCM using the efficient GCD algorithm.
def lcm(a, b):
    if a == 0 or b == 0:
        return 0
    return abs(a // gcd_euclid(a, b) * b)

print(lcm(24, 16))
print(lcm(9, 17))
```

**Expected output**
```text
48
153
```

Dividing before multiplying helps avoid unnecessarily large intermediate values in languages with fixed-size integers.

---

## 5. Diophantine Equations

A **Diophantine equation** is an equation for which integer solutions are required.

A common linear form is:

\[
ax+by=c
\]

Here, \(a,b,c\) are known integers and we seek integer values of \(x,y\).

Example from the workshop:

\[
187x+55y=121
\]

One solution is \(x=3,\ y=-8\), because:

\[
187(3)+55(-8)=561-440=121
\]

### 5.1 Existence of Integer Solutions

The linear Diophantine equation

\[
ax+by=c
\]

has an integer solution **if and only if**:

\[
\gcd(a,b)\mid c
\]

If the GCD does not divide \(c\), there is no integer solution.

```python
# Determine whether ax + by = c can have integer solutions.
def diophantine_has_solution(a, b, c):
    if a == 0 and b == 0:
        return c == 0
    return c % gcd_euclid(a, b) == 0

print(diophantine_has_solution(10, 6, 14))
print(diophantine_has_solution(187, 55, 45))
```

**Expected output**
```text
True
False
```

### 5.2 Finding All Solutions

Suppose \(d=\gcd(a,b)\), \(a=dp\), \(b=dq\), and \((x_0,y_0)\) is one solution. Then all integer solutions are:

\[
x=x_0+tq,\qquad y=y_0-tp,\qquad t\in\mathbb Z
\]

For \(3x+5y=22\), one solution is \((9,-1)\). Therefore:

\[
x=9+5t,\qquad y=-1-3t
\]

```python
# Find one integer solution using Extended Euclid.
def solve_diophantine(a, b, c):
    if a == 0 and b == 0:
        return (0, 0) if c == 0 else None

    g, x0, y0 = extended_gcd(a, b)

    # No solution exists unless the GCD divides c.
    if c % g != 0:
        return None

    scale = c // g
    return x0 * scale, y0 * scale

a, b, c = 3, 5, 22
solution = solve_diophantine(a, b, c)
print("One solution (x, y):", solution)

# Verify the returned solution.
x0, y0 = solution
print("Left-hand side:", a*x0 + b*y0)
```

**Expected output**
```text
One solution (x, y): (9, -1)
Left-hand side: 22
```

---

## 6. Modular Arithmetic and Remainders

The remainder after dividing integer \(a\) by positive integer \(n\) is written as:

\[
a\bmod n
\]

Two integers \(a\) and \(b\) are **congruent modulo \(n\)** if they have the same remainder:

\[
a\equiv b\pmod n
\]

Equivalently:

\[
n\mid(a-b)
\]

Example:

\[
17\equiv5\pmod{12}
\]

because \(17-5=12\), which is divisible by 12.

### 6.1 Congruence Properties

If \(a\equiv b\pmod n\) and \(c\equiv d\pmod n\), then:

\[
a+c\equiv b+d\pmod n
\]
\[
ac\equiv bd\pmod n
\]

Powers also preserve congruence:

\[
a^k\equiv b^k\pmod n
\]

for non-negative integer \(k\).

```python
# Demonstrate addition and multiplication with modular congruence.
a, b, n = 17, 5, 12
c, d = 8, 2

print("17 mod 12 =", a % n)
print("5 mod 12 =", b % n)
# Since a and b are congruent, adding or multiplying both by the same c preserves congruence.
print("Addition check:", (a + c) % n, (b + c) % n)
print("Multiplication check:", (a * c) % n, (b * c) % n)
```

**Expected output**
```text
17 mod 12 = 5
5 mod 12 = 5
Addition check: 1 1
Multiplication check: 4 4
```

The two results in each check are equal, demonstrating that adding or multiplying congruent values by the same integer preserves congruence.

### 6.2 Divisibility Criteria

Common decimal divisibility rules:

- Divisible by 2: last digit is 0, 2, 4, 6 or 8.
- Divisible by 5: last digit is 0 or 5.
- Divisible by 10: last digit is 0.
- Divisible by 3: sum of decimal digits is divisible by 3.
- Divisible by 9: sum of decimal digits is divisible by 9.

The last-digit rules come from the fact that \(10\) is divisible by 2 and 5. The digit-sum rules follow from \(10\equiv1\pmod 3\) and \(10\equiv1\pmod 9\).

```python
# Check divisibility rules for a positive integer.
def digit_sum(n):
    return sum(int(digit) for digit in str(abs(n)))

number = 738
print("Divisible by 2:", number % 2 == 0)
print("Divisible by 3:", digit_sum(number) % 3 == 0)
print("Divisible by 5:", number % 5 == 0)
print("Divisible by 9:", digit_sum(number) % 9 == 0)
```

**Expected output**
```text
Divisible by 2: True
Divisible by 3: True
Divisible by 5: False
Divisible by 9: True
```

---

## 7. Modular Multiplicative Inverse and Division

A multiplicative inverse of \(a\) modulo \(n\) is an integer \(a^{-1}\) satisfying:

\[
a\cdot a^{-1}\equiv1\pmod n
\]

The inverse exists **if and only if**:

\[
\gcd(a,n)=1
\]

The extended Euclidean algorithm finds it. If:

\[
ax+ny=1
\]

then \(x\) is the inverse of \(a\) modulo \(n\).

Example:

\[
2^{-1}\equiv5\pmod9
\]

because \(2\times5=10\equiv1\pmod9\).

Modular division is multiplication by the modular inverse:

\[
\frac{b}{a}\pmod n \equiv b\cdot a^{-1}\pmod n
\]

```python
# Find the modular inverse of a modulo n.
def modular_inverse(a, n):
    g, x, _ = extended_gcd(a, n)

    # An inverse exists only when a and n are coprime.
    if g != 1:
        return None

    return x % n

inverse = modular_inverse(2, 9)
print("Inverse of 2 modulo 9:", inverse)
print("Verification:", (2 * inverse) % 9)

# Modular division: 7 / 2 modulo 9.
print("7 / 2 modulo 9:", (7 * inverse) % 9)
```

**Expected output**
```text
Inverse of 2 modulo 9: 5
Verification: 1
7 / 2 modulo 9: 8
```

If \(\gcd(a,n)\ne1\), an inverse does not exist. For example, 3 has no inverse modulo 6.

---

## 8. Chinese Remainder Theorem (CRT)

The **Chinese Remainder Theorem** says that if \(a\) and \(b\) are coprime, then for any remainders \(r_a,r_b\), there is a unique solution modulo \(ab\) to:

\[
x\equiv r_a\pmod a
\]
\[
x\equiv r_b\pmod b
\]

Example:

\[
x\equiv2\pmod3,\qquad x\equiv3\pmod5
\]

The solution is \(x=8\pmod{15}\), because 8 leaves remainder 2 on division by 3 and remainder 3 on division by 5.

```python
# Solve two congruences with pairwise-coprime moduli.
def chinese_remainder_two(r1, m1, r2, m2):
    if gcd_euclid(m1, m2) != 1:
        raise ValueError("The two moduli must be coprime.")

    # Find the inverse of m1 modulo m2.
    inv = modular_inverse(m1, m2)

    # Construct the solution modulo m1*m2.
    x = r1 + m1 * (((r2 - r1) * inv) % m2)
    return x % (m1 * m2)

x = chinese_remainder_two(2, 3, 3, 5)
print("Smallest non-negative solution:", x)
print("Check modulo 3:", x % 3)
print("Check modulo 5:", x % 5)
```

**Expected output**
```text
Smallest non-negative solution: 8
Check modulo 3: 2
Check modulo 5: 3
```

For more than two pairwise-coprime moduli, the same idea can be applied repeatedly. CRT is also useful in computations with large integers by working with remainders modulo several coprime moduli.

---

## 9. Fast Modular Exponentiation

Modular exponentiation computes:

\[
b^e\bmod m
\]

Computing \(b^e\) first may create an enormous integer. Instead, repeatedly multiply and take the remainder. A faster method uses **repeated squaring** and the binary representation of the exponent.

For example:

\[
13=8+4+1=1101_2
\]

Therefore:

\[
b^{13}=b^8\cdot b^4\cdot b
\]

Repeated squaring reduces the number of multiplications from \(O(e)\) to \(O(\log e)\).

```python
# Compute (base ** exponent) modulo modulus using repeated squaring.
def fast_modular_power(base, exponent, modulus):
    if exponent < 0:
        raise ValueError("Exponent must be non-negative.")
    if modulus <= 0:
        raise ValueError("Modulus must be positive.")

    result = 1
    base %= modulus

    while exponent > 0:
        # If the current binary digit is 1, include this power.
        if exponent % 2 == 1:
            result = (result * base) % modulus

        # Square the base for the next binary digit.
        base = (base * base) % modulus
        exponent //= 2

    return result

print(fast_modular_power(7, 13, 11))
print(pow(7, 13, 11))  # Python's built-in modular exponentiation.
```

**Expected output**
```text
2
2
```

---

## 10. Fermat's Little Theorem

**Fermat's Little Theorem:** If \(p\) is prime and \(p\nmid a\), then:

\[
a^{p-1}\equiv1\pmod p
\]

An equivalent form valid for every integer \(a\) is:

\[
a^p\equiv a\pmod p
\]

The theorem is useful for modular arithmetic, cryptography and probabilistic primality testing. Its converse is not always true: some composite numbers pass a Fermat test for a particular base.

```python
# Verify Fermat's Little Theorem for a prime p and a not divisible by p.
a, p = 3, 7
print("a^(p-1) mod p =", pow(a, p - 1, p))
print("Expected value =", 1)
```

**Expected output**
```text
a^(p-1) mod p = 1
Expected value = 1
```

---

## 11. Euler's Totient Function

Euler's totient function \(\phi(n)\) counts the integers from 1 to \(n\) that are coprime to \(n\). Equivalently, it counts the residue classes modulo \(n\) that are relatively prime to \(n\).

Examples:

\[
\phi(1)=1,\quad \phi(2)=1,\quad \phi(3)=2,\quad \phi(10)=4
\]

If \(p\) is prime:

\[
\phi(p)=p-1
\]

If \(p\) and \(q\) are distinct primes:

\[
\phi(pq)=(p-1)(q-1)
\]

For a prime factorization \(n=\prod p_i^{a_i}\):

\[
\phi(n)=n\prod_{p\mid n}\left(1-\frac1p\right)
\]

```python
# Count integers from 1 through n that are coprime to n.
def euler_phi(n):
    if n < 1:
        raise ValueError("n must be a positive integer.")

    count = 0
    for value in range(1, n + 1):
        if gcd_euclid(value, n) == 1:
            count += 1
    return count

print("phi(1) =", euler_phi(1))
print("phi(10) =", euler_phi(10))
print("phi(7) =", euler_phi(7))
```

**Expected output**
```text
phi(1) = 1
phi(10) = 4
phi(7) = 6
```

This simple implementation is intended for learning. More efficient methods use prime factorization.

---

## 12. Euler's Theorem

Euler's theorem generalizes Fermat's Little Theorem.

If:

\[
\gcd(a,n)=1
\]

then:

\[
a^{\phi(n)}\equiv1\pmod n
\]

For prime \(n=p\), \(\phi(p)=p-1\), so Euler's theorem becomes Fermat's Little Theorem.

```python
# Verify Euler's theorem for a=3 and n=10.
a, n = 3, 10
phi_n = euler_phi(n)

print("phi(n) =", phi_n)
print("a^phi(n) mod n =", pow(a, phi_n, n))
```

**Expected output**
```text
phi(n) = 4
a^phi(n) mod n = 1
```

The coprimality condition is essential.

---

## 13. Cryptography and Public-Key Idea

Cryptography studies methods for protecting information. The workshop introduces the problem of sharing a secret key safely and motivates **public-key cryptography**.

A public-key system uses related keys:
- A public key can be shared.
- A private key must be kept secret.
- Encryption and decryption are designed so that knowledge of the public key alone does not practically reveal the private key.

Number-theoretic tools used in this area include:
- Prime numbers and factorization.
- GCD and coprimality.
- Modular inverses.
- Fast modular exponentiation.
- Euler's totient function and Euler's theorem.

### A small educational RSA example

Choose two small primes \(p=5\), \(q=11\).

\[
n=pq=55,\qquad \phi(n)=(p-1)(q-1)=40
\]

Choose \(e=3\), which is coprime to 40. Its modular inverse is \(d=27\), because:

\[
3\times27=81\equiv1\pmod{40}
\]

For a small message \(m=7\):

\[
c=m^e\bmod n=7^3\bmod55=13
\]
\[
m=c^d\bmod n=13^{27}\bmod55=7
\]

```python
# Educational RSA demonstration with tiny primes.
# These values are insecure and must never be used for real encryption.
p, q = 5, 11
n = p * q
phi_n = (p - 1) * (q - 1)

e = 3
d = modular_inverse(e, phi_n)

message = 7
ciphertext = pow(message, e, n)
decrypted = pow(ciphertext, d, n)

print("Public key (e, n):", (e, n))
print("Private exponent d:", d)
print("Message:", message)
print("Encrypted:", ciphertext)
print("Decrypted:", decrypted)
```

**Expected output**
```text
Public key (e, n): (3, 55)
Private exponent d: 27
Message: 7
Encrypted: 13
Decrypted: 7
```

This is a classroom demonstration only. Real RSA requires very large, securely generated primes, padding, and a vetted cryptographic library.

---

## 14. Prime Numbers

A **prime number** is a natural number greater than 1 that cannot be written as a product of two smaller natural numbers. Equivalently, it has exactly two positive divisors: 1 and itself.

Examples: 2, 3, 5, 7, 11, 13, 17, 19.

A **composite number** has more than two positive divisors. The number 1 is neither prime nor composite. The only even prime is 2.

Prime numbers are the basic building blocks of positive integers. The Fundamental Theorem of Arithmetic says that every integer greater than 1 has a unique prime factorization, apart from the order of the factors.

### 14.1 Prime Distribution and Infinitude

There are infinitely many prime numbers. Euclid's classical argument gives the central idea:

1. Assume there are only finitely many primes \(p_1,p_2,\ldots,p_k\).
2. Form \(N=p_1p_2\cdots p_k+1\).
3. None of the listed primes divides \(N\), because each leaves remainder 1.
4. But every integer greater than 1 has a prime divisor.
5. This produces a prime not in the supposedly complete list, a contradiction.

The prime-number PDF also mentions other approaches to infinitude, including harmonic-series, Goldbach, Saidak and topological arguments, as well as constructions related to primes of the forms \(4k+1\) and \(4k+3\). These are listed as topics; their full proofs are not developed in the supplied slides.

```python
# Demonstrate Euclid's construction using a finite list of initial primes.
known_primes = [2, 3, 5, 7, 11]
N = 1
for prime in known_primes:
    N *= prime
N += 1

print("Constructed N:", N)
print("Remainder when divided by each listed prime:",
      [N % prime for prime in known_primes])
```

**Expected output**
```text
Constructed N: 2311
Remainder when divided by each listed prime: [1, 1, 1, 1, 1]
```

This construction does not say that \(N\) itself must be prime; it says that none of the primes in the assumed complete list can divide it.

### 14.2 Dirichlet's Theorem and Prime Number Theorem

**Dirichlet's theorem on arithmetic progressions:** If positive integers \(a\) and \(b\) are coprime, then the arithmetic progression

\[
ak+b,\quad k=0,1,2,\ldots
\]

contains infinitely many primes.

The coprimality condition is necessary. If \(\gcd(a,b)>1\), every term shares a common divisor greater than 1 (apart from possible exceptional initial terms).

**Prime Number Theorem:** Let \(\pi(x)\) count primes not exceeding \(x\). As \(x\) becomes large:

\[
\pi(x)\sim\frac{x}{\ln x}
\]

This means that the ratio of \(\pi(x)\) to \(x/\ln x\) approaches 1 as \(x\to\infty\). It describes the approximate density of primes; it is not an exact formula for every \(x\).

```python
# Count primes up to x using trial division, then compare with x / ln(x).
import math

def is_prime_for_count(n):
    if n < 2:
        return False
    divisor = 2
    while divisor * divisor <= n:
        if n % divisor == 0:
            return False
        divisor += 1
    return True

def count_primes_up_to(x):
    return sum(1 for n in range(2, x + 1) if is_prime_for_count(n))

x = 1000
actual = count_primes_up_to(x)
approximation = x / math.log(x)

print("pi(1000) =", actual)
print("x / ln(x) =", round(approximation, 2))
```

**Expected output**
```text
pi(1000) = 168
x / ln(x) = 144.76
```

### 14.3 Prime Conjectures

A **conjecture** is a mathematical statement believed to be true but not yet proved.

Topics listed in the supplied prime-number slides include:

- **Goldbach conjecture:** Every even integer greater than 2 can be expressed as the sum of two primes.
- **Twin prime conjecture:** There are infinitely many pairs of primes that differ by 2.
- **Waring's prime-number conjecture (as named in the slides):** Every odd number greater than 3 is either prime or the sum of three primes.
- **Prime values of \(n^2+1\):** The slides list the question of whether infinitely many primes have this form.
- **Prime between consecutive squares:** The slides state the question of whether there is always a prime between \(n^2\) and \((n+1)^2\).
- **Prime spirals and Chebyshev's bias:** Additional topics concerning patterns in the distribution of primes.

The notebook can test examples for small values, but finite experiments cannot prove an infinite conjecture.

```python
# A small helper for checking primality in the Goldbach example.
def is_prime(n):
    if n < 2:
        return False
    divisor = 2
    while divisor * divisor <= n:
        if n % divisor == 0:
            return False
        divisor += 1
    return True

# Find a Goldbach representation for an even number.
def goldbach_pair(n):
    if n <= 2 or n % 2 != 0:
        return None

    for p in range(2, n):
        if is_prime(p) and is_prime(n - p):
            return p, n - p
    return None

print("Goldbach pair for 28:", goldbach_pair(28))
```

**Expected output**
```text
Goldbach pair for 28: (5, 23)
```

### 14.4 Generating Primes and Polynomial Examples

The slides discuss the polynomial:

\[
f(n)=n^2+n+41
\]

It produces prime values for several small non-negative integers, but it does not produce a prime for every integer. For example, \(f(40)=1681=41^2\).

```python
# Evaluate Euler's famous quadratic polynomial for selected inputs.
def euler_polynomial(n):
    return n*n + n + 41

for value in [0, 1, 2, 10, 39, 40]:
    result = euler_polynomial(value)
    print(f"n={value:2d}, f(n)={result:4d}, prime={is_prime(result)}")
```

**Expected output**
```text
n= 0, f(n)=  41, prime=True
n= 1, f(n)=  43, prime=True
n= 2, f(n)=  47, prime=True
n=10, f(n)= 151, prime=True
n=39, f(n)= 1601, prime=True
n=40, f(n)= 1681, prime=False
```

The slides also mention a result of Matiyasevich concerning a polynomial in 10 variables. This is an advanced result and is not implemented in this beginner notebook.

---

## 15. Primality Testing

A primality test determines whether an integer is prime or composite. It is important to distinguish a **proof-producing deterministic test** from a **probabilistic test** that gives a confidence level or can be fooled by special composite numbers.

### 15.1 Trial Division

If \(n\) is composite, it has a factor no larger than \(\sqrt n\). Therefore, to test primality, it is enough to try divisors up to the square root.

```python
# Deterministic trial-division primality test.
def is_prime(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False

    divisor = 3
    while divisor * divisor <= n:
        if n % divisor == 0:
            return False
        divisor += 2  # Skip even divisors.
    return True

print(is_prime(29))
print(is_prime(91))
```

**Expected output**
```text
True
False
```

### 15.2 Sieve of Eratosthenes

The **Sieve of Eratosthenes** finds all primes up to a limit \(n\):

1. Create a list of integers from 0 to \(n\).
2. Mark 0 and 1 as non-prime.
3. Starting with 2, mark its multiples as composite.
4. Continue for prime candidates up to \(\sqrt n\).
5. The unmarked numbers are prime.

```python
# Generate all prime numbers up to limit using the Sieve of Eratosthenes.
def sieve_of_eratosthenes(limit):
    if limit < 2:
        return []

    # Initially assume every number is prime.
    is_prime_flag = [True] * (limit + 1)
    is_prime_flag[0] = False
    is_prime_flag[1] = False

    candidate = 2
    while candidate * candidate <= limit:
        if is_prime_flag[candidate]:
            # Start at candidate squared; smaller multiples were handled earlier.
            for multiple in range(candidate * candidate, limit + 1, candidate):
                is_prime_flag[multiple] = False
        candidate += 1

    return [number for number, flag in enumerate(is_prime_flag) if flag]

print(sieve_of_eratosthenes(50))
```

**Expected output**
```text
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]
```

### 15.3 Wheel Factorization

Wheel factorization skips candidate numbers that are divisible by small primes. The slides describe the **wheel of 30**, based on residues:

\[
1,7,11,13,17,19,23,29\pmod{30}
\]

These are the residues relatively prime to 30. Every prime greater than 5 must lie in one of these residue classes. Being in one of these classes does not guarantee primality; further testing is still required.

```python
# Show the residues modulo 30 that are coprime to 30.
wheel_residues = [r for r in range(30) if gcd_euclid(r, 30) == 1]
print(wheel_residues)
```

**Expected output**
```text
[1, 7, 11, 13, 17, 19, 23, 29]
```

### 15.4 Pseudoprimes and Fermat's Primality Test

A **pseudoprime to base \(a\)** is a composite number that passes a Fermat-style test for that base:

\[
a^{n-1}\equiv1\pmod n
\]

when \(\gcd(a,n)=1\).

The slides give these examples:
- 341 is a pseudoprime to base 2, but not base 3.
- 91 is a pseudoprime to base 3, but not base 2.
- 561 is a Carmichael number and passes the Fermat congruence for every base coprime to it.

A Fermat test can prove that a number is composite when a congruence fails, but passing the test does **not** prove primality.

```python
# Return True when n passes the Fermat test for the selected base.
# Passing is not a proof that n is prime.
def fermat_test(n, base):
    if n < 2:
        return False
    if gcd_euclid(base, n) != 1:
        return False
    return pow(base, n - 1, n) == 1

print("341, base 2:", fermat_test(341, 2))
print("341, base 3:", fermat_test(341, 3))
print("91, base 3:", fermat_test(91, 3))
print("91, base 2:", fermat_test(91, 2))
```

**Expected output**
```text
341, base 2: True
341, base 3: False
91, base 3: True
91, base 2: False
```

### 15.5 Carmichael Numbers

A **Carmichael number** is a composite positive integer \(n\) for which:

\[
a^n\equiv a\pmod n
\]

for every integer \(a\). Equivalently, for every \(a\) coprime to \(n\), \(a^{n-1}\equiv1\pmod n\).

The slides state Korselt's criterion: \(n\) is a Carmichael number if and only if it is positive, composite, square-free, and for every prime divisor \(p\) of \(n\), \(p-1\) divides \(n-1\).

Examples listed in the slides: 561, 1105, 1729, 2465 and 2821.

```python
# Check the Carmichael congruence for every base coprime to n.
# This direct check is intended only for small numbers.
def passes_all_coprime_fermat_bases(n):
    if n < 2 or is_prime(n):
        return False

    for base in range(1, n):
        if gcd_euclid(base, n) == 1:
            if pow(base, n - 1, n) != 1:
                return False
    return True

print("561 is composite:", not is_prime(561))
print("561 passes all coprime bases:", passes_all_coprime_fermat_bases(561))
```

**Expected output**
```text
561 is composite: True
561 passes all coprime bases: True
```

### 15.6 Lucas' Primality Test and the n-1 Test

The slides present Lucas' theorem in the following form. Let \(n>1\). If for every prime factor \(q\) of \(n-1\), there is an integer \(a\) such that:

\[
a^{n-1}\equiv1\pmod n
\]
\[
a^{(n-1)/q}\not\equiv1\pmod n
\]

then \(n\) is prime.

The slides also describe a partial-factorization version, the **n-1 test**: write \(n-1=FR\), where \(F>R\), \(\gcd(F,R)=1\), and the factorization of \(F\) is known. Suitable modular conditions for each prime factor of \(F\) can certify primality.

These are certificate-based primality ideas. A complete general-purpose implementation needs careful factorization and witness handling, so this notebook introduces the condition but does not claim to implement a fully general Lucas certificate verifier.

```python
# Illustrate the Lucas condition for n=7.
# The prime factors of n-1=6 are 2 and 3.
n = 7
for q in [2, 3]:
    witnesses = [
        a for a in range(2, n)
        if pow(a, n - 1, n) == 1
        and pow(a, (n - 1) // q, n) != 1
    ]
    print(f"q={q}, witnesses={witnesses}")
```

**Expected output**
```text
q=2, witnesses=[3, 5, 6]
q=3, witnesses=[2, 3, 4, 5]
```

### 15.7 Lucas-Lehmer Test and Mersenne Primes

A **Mersenne number** has the form:

\[
M_p=2^p-1
\]

When \(M_p\) is prime, it is called a **Mersenne prime**. If \(2^p-1\) is prime, then \(p\) must itself be prime.

The slides list small exponents such as \(2,3,5,7,13,17,19,31,61,89,107,127\). Not every number of the form \(2^n-1\) is prime; for example, \(2^{11}-1=2047=23\times89\).

For prime \(p>2\), the Lucas-Lehmer sequence is:

\[
s_0=4,\qquad s_{k+1}=s_k^2-2\pmod{2^p-1}
\]

Then \(2^p-1\) is prime if and only if \(s_{p-2}\equiv0\pmod{2^p-1}\).

```python
# Lucas-Lehmer test for Mersenne numbers with prime exponent p.
def lucas_lehmer(p):
    if p == 2:
        return True
    if not is_prime(p):
        return False

    mersenne = (1 << p) - 1
    s = 4

    # Perform p-2 recurrence steps, reducing modulo M_p each time.
    for _ in range(p - 2):
        s = (s * s - 2) % mersenne

    return s == 0

for exponent in [2, 3, 5, 7, 11, 13]:
    print(f"p={exponent}, 2^p-1 prime? {lucas_lehmer(exponent)}")
```

**Expected output**
```text
p=2, 2^p-1 prime? True
p=3, 2^p-1 prime? True
p=5, 2^p-1 prime? True
p=7, 2^p-1 prime? True
p=11, 2^p-1 prime? False
p=13, 2^p-1 prime? True
```

---

## 16. Further Properties of Prime Numbers

### 16.1 Primitive Roots and Multiplicative Order

For a prime \(p\), the non-zero residues modulo \(p\) are:

\[
1,2,\ldots,p-1
\]

If \(a\) is not divisible by \(p\), multiplication by \(a\) permutes these non-zero residues. This is one of the ideas behind Fermat's Little Theorem.

The **multiplicative order** of \(a\) modulo \(n\) is the smallest positive integer \(k\) such that:

\[
a^k\equiv1\pmod n
\]

when the inverse exists. A **primitive root modulo \(p\)** is a number whose multiplicative order is \(p-1\); its powers generate every non-zero residue modulo \(p\).

```python
# Calculate the multiplicative order of a modulo n, if it exists.
def multiplicative_order(a, n):
    if n <= 1 or gcd_euclid(a, n) != 1:
        return None

    value = 1
    for order in range(1, n + 1):
        value = (value * a) % n
        if value == 1:
            return order
    return None

print("Order of 2 modulo 7:", multiplicative_order(2, 7))
```

**Expected output**
```text
Order of 2 modulo 7: 3
```

Since the order is 3 rather than 6, 2 is not a primitive root modulo 7.

### 16.2 Prime Characterizations

The prime-number slides list several equivalent characterizations for \(p>1\):

1. \(p\) is prime if and only if every non-zero residue modulo \(p\) is invertible.
2. \(p\) is prime if and only if \(\phi(p)=p-1\).
3. For prime \(p\), the only solutions to \(x^2\equiv1\pmod p\) are \(x\equiv1\) and \(x\equiv p-1\pmod p\).

The prime slides also mention the existence of primitive roots and Lucas' theorem as primality tools.

```python
# Check the square-root-of-one residues modulo a prime.
p = 7
solutions = [x for x in range(p) if (x*x) % p == 1]
print("Solutions of x^2 = 1 (mod 7):", solutions)
```

**Expected output**
```text
Solutions of x^2 = 1 (mod 7): [1, 6]
```

---

## 17. Divisor Functions and Antiprimes

If the prime factorization of \(n\) is:

\[
n=p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}
\]

then the number of positive divisors is:

\[
d(n)=(a_1+1)(a_2+1)\cdots(a_k+1)
\]

For example:

\[
12=2^2\cdot3^1,\qquad d(12)=(2+1)(1+1)=6
\]

The sum-of-divisors function adds all positive divisors. A **highly composite number** (called an antiprime in the supplied slides) has more positive divisors than every smaller positive integer.

The slides list examples such as 1, 2, 4, 6, 12, 24, 36, 48, 60 and 360.

```python
# Count positive divisors and sum them.
def divisor_count(n):
    if n < 1:
        raise ValueError("n must be positive.")
    count = 0
    for d in range(1, n + 1):
        if n % d == 0:
            count += 1
    return count

def divisor_sum(n):
    if n < 1:
        raise ValueError("n must be positive.")
    return sum(d for d in range(1, n + 1) if n % d == 0)

print("Number of divisors of 12:", divisor_count(12))
print("Sum of divisors of 12:", divisor_sum(12))
```

**Expected output**
```text
Number of divisors of 12: 6
Sum of divisors of 12: 28
```

```python
# Find highly composite numbers in a small range.
def highly_composite_numbers(limit):
    results = []
    best_count = 0

    for n in range(1, limit + 1):
        current_count = divisor_count(n)
        if current_count > best_count:
            results.append(n)
            best_count = current_count

    return results

print(highly_composite_numbers(60))
```

**Expected output**
```text
[1, 2, 4, 6, 12, 24, 36, 48, 60]
```

---

## 18. Fundamental Theorem of Arithmetic

The **Fundamental Theorem of Arithmetic** states that every integer greater than 1 can be represented as a product of prime numbers in exactly one way, apart from the order of the factors.

Example:

\[
60=2^2\times3\times5
\]

Prime factorization is important in number theory and cryptography. Multiplying two primes is straightforward, while recovering the prime factors of a sufficiently large product can be computationally difficult with known classical methods.

```python
# Return the prime factorization of a positive integer.
def prime_factorization(n):
    if n < 1:
        raise ValueError("Enter a positive integer.")
    factors = []
    divisor = 2

    while divisor * divisor <= n:
        while n % divisor == 0:
            factors.append(divisor)
            n //= divisor
        divisor += 1

    if n > 1:
        factors.append(n)

    return factors

print(prime_factorization(60))
```

**Expected output**
```text
[2, 2, 3, 5]
```

---

## 19. Practice Problems

Try these problems in the notebook before checking the outputs.

1. Find \(\gcd(252,105)\) using Euclid's algorithm.
2. Find \(\operatorname{lcm}(18,30)\).
3. Find integers \(x,y\) such that \(35x+15y=5\).
4. Find the inverse of 7 modulo 26.
5. Compute \(7^{128}\bmod 13\) using fast modular exponentiation.
6. Find all prime numbers up to 100 using the Sieve of Eratosthenes.
7. Check whether 341 passes the Fermat test to base 2.
8. Find a Goldbach pair for 50.
9. Compute \(\phi(36)\).
10. Find the prime factorization of 2024.

```python
# Practice answer checker: run after studying the algorithms above.
print("1. GCD:", gcd_euclid(252, 105))
print("2. LCM:", lcm(18, 30))
print("3. One solution:", solve_diophantine(35, 15, 5))
print("4. Inverse:", modular_inverse(7, 26))
print("5. Modular power:", fast_modular_power(7, 128, 13))
print("6. Primes up to 100:", sieve_of_eratosthenes(100))
print("7. 341 passes base 2:", fermat_test(341, 2))
print("8. Goldbach pair:", goldbach_pair(50))
print("9. phi(36):", euler_phi(36))
print("10. Factorization:", prime_factorization(2024))
```

**Expected output**
```text
1. GCD: 21
2. LCM: 90
3. One solution: (1, -2)
4. Inverse: 15
5. Modular power: 3
6. Primes up to 100: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
7. 341 passes base 2: True
8. Goldbach pair: (3, 47)
9. phi(36): 12
10. Factorization: [2, 2, 2, 11, 23]
```

---

## 20. References and Scope Notes

### Uploaded study materials

1. **Number_therory2.pdf** — 308-page number theory and cryptography workshop material. Topics covered include GCD, Euclid's and Extended Euclid's algorithms, LCM, Diophantine equations, modular division, remainders, Chinese Remainder Theorem, fast modular exponentiation, Fermat's Little Theorem, Euler's totient function and Euler's theorem.
2. **Number_theory3.pdf** — 25-page *Prime Numbers* presentation by the Maths and Physics Club, IIT Bombay (December 24, 2020). Topics include prime distribution, infinitude of primes, Dirichlet's theorem, the Prime Number Theorem, conjectures, primality testing, pseudoprimes, Carmichael numbers, Lucas tests, Mersenne primes, divisor functions and antiprimes.

### Important notes

- This README is an expanded beginner-friendly study guide based on the two uploaded PDFs. Explanations and Python examples are educational additions to help practise the listed concepts.
- Some slides list advanced proof topics without giving their complete proofs. Those are identified as advanced topics rather than presented as fully proved here.
- All code is intended for Python 3 and can be run in Google Colab or Jupyter Notebook.
- The RSA example uses tiny numbers only to demonstrate the mathematics. It is not secure for real-world use.
- A finite program output can illustrate a theorem or conjecture, but it cannot prove a statement about infinitely many integers.

**Prepared by:** Abdur Rahim  
**Student ID:** IT22053
