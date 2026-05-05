import random

# Define the file sizes
sizes = [100, 1000, 10000, 100000, 1000000]

# Generate files with random lowercase characters
for size in sizes:
    filename = f"char_{size}.txt"
    chars = [random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(size)]
    
    with open(filename, 'w') as f:
        for ch in chars:
            f.write(ch + '\n')
    
    print(f"Generated {filename} with {size} random characters")

# Generate files with random integers
for size in sizes:
    filename = f"int_{size}.txt"
    ints = [random.randint(0, 99) for _ in range(size)]
    
    with open(filename, 'w') as f:
        for n in ints:
            f.write(str(n) + '\n')
    
    print(f"Generated {filename} with {size} random ints")