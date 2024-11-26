import cmath

def solve_cubic(a, b, c, d):
    """Giải phương trình bậc 3 ax^3 + bx^2 + cx + d = 0"""
    if a == 0:
        raise ValueError("Không phải phương trình bậc 3!")
    a, b, c = b/a, c/a, d/a
    q = (3*c - b**2) / 9
    r = (9*b*c - 27*d - 2*b**3) / 54
    delta = q**3 + r**2  # Discriminant

    if delta > 0:
        s = cmath.exp(cmath.log(r + cmath.sqrt(delta)) / 3)
        t = cmath.exp(cmath.log(r - cmath.sqrt(delta)) / 3)
        return [s + t - b/3]
    elif delta == 0:
        s = (r)**(1/3)
        return [2*s - b/3, -s - b/3]
    else:
        theta = cmath.acos(r / cmath.sqrt(-q**3))
        roots = [
            2 * cmath.sqrt(-q) * cmath.cos(theta / 3) - b/3,
            2 * cmath.sqrt(-q) * cmath.cos((theta + 2*cmath.pi) / 3) - b/3,
            2 * cmath.sqrt(-q) * cmath.cos((theta + 4*cmath.pi) / 3) - b/3
        ]
        return roots

def solve_quartic_manual(a, b, c, d, e):
    """Giải phương trình bậc 4 tổng quát ax^4 + bx^3 + cx^2 + dx + e = 0"""
    if a == 0:
        raise ValueError("Không phải phương trình bậc 4!")
    # Chuẩn hóa
    b, c, d, e = b/a, c/a, d/a, e/a
    
    # Loại bỏ x^3
    p = c - (3*b**2)/8
    q = d - (b*c)/2 + (b**3)/8
    r = e - (b*d)/4 + (b**2*c)/16 - (3*b**4)/256
    
    # Giải phương trình bậc 3 bổ trợ
    cubic_coefficients = [1, 2*p, p**2 - 4*r, -q**2]
    u_roots = solve_cubic(*cubic_coefficients)
    u = max(u_roots, key=lambda x: x.real)
    
    # Phương trình con bậc 2
    sqrt_term = cmath.sqrt(p + 2*u)
    quad1 = [1, sqrt_term, u + q / sqrt_term]
    quad2 = [1, -sqrt_term, u - q / sqrt_term]
    
    # Tìm nghiệm của hai phương trình bậc 2
    roots = []
    for quad in [quad1, quad2]:
        delta = quad[1]**2 - 4*quad[0]*quad[2]
        roots.append((-quad[1] + cmath.sqrt(delta)) / (2 * quad[0]))
        roots.append((-quad[1] - cmath.sqrt(delta)) / (2 * quad[0]))
    
    # Đổi về biến x
    return [root - b/4 for root in roots]

# Ví dụ
a, b, c, d, e = 1, -3, 3, -1, -6
solutions = solve_quartic_manual(a, b, c, d, e)
print("Các nghiệm của phương trình là:", solutions)
