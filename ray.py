# Example ray test with numpy

import numpy as np

def main() -> None:
    origin = np.array([0, 1, -5])
    direction = np.array([0, 0, 1])
    oc = origin - np.array([0, 0, 0])

    a = np.dot(direction, direction)
    b = 2.0 * np.dot(direction, oc)
    c = np.dot(oc, oc) - 1.0
    d = (b * b) - (4 * a * c)

    print(f"a: {a}, b: {b}, c: {c}, d: {d}")

    if d >= 0.0:
        t0 = (-b - np.sqrt(d) / (2.0 * a))
        t1 = (-b + np.sqrt(d) / (2.0 * a))
        print(f"t0: {t0}, t1: {t1}")

if __name__ == "__main__":
    main()
