highest_degree = input("Enter Highest Exponent: ")
eq1 = []
for i in range(int(highest_degree)):
    num = input("Enter term" + str(i + 1) + ": ")
    eq1.append(int(num))

eq2 = []
for i in range(int(highest_degree)):
    num = input("Enter term" + str(i + 1) + ": " )
    eq2.append(int(num))

for i in range(int(highest_degree)):
    print(eq1[i] * eq2[i], end=" ")