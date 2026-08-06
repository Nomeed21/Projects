import random
def generate_random_array(size):
    array = []
    for i in range(size):
        array.append(random.randint(1, size))
    return array



def worst_case(array):
    for i in range(len(array) - 1):
        swapped = False
        for j in range(len(array) - 1 - i):
            if array[j] < array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
                swapped = True
        if not swapped:
            break
    return array

#bubble sort
def bubble_sort(array):
    counter = 0
    swaps = 0
    for i in range(len(array) - 1):
        counter += 1
        swapped = False
        for j in range(len(array) - 1 - i):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
                swapped = True
                swaps +=1
        if not swapped:
            break
    return counter + swaps

#selection sort
def selection_sort(array):
    operations = 0
    for i in range(len(array) - 1):
        min_index = i
        for j in range(i + 1, len(array)):
            if array[j] < array[min_index]:
                min_index = j
            operations += 1
        array[i], array[min_index] = array[min_index], array[i]
        operations += 1
    print("Operations: ", operations)
    return array

array1= generate_random_array(10)
print(array1)
array2= generate_random_array(20)
print(array2)
first = round(bubble_sort(array1))
print(first)
second = round(bubble_sort(array2))
print(second)
print(second // first)
if second // first == 1:
    print("O(1)")
elif second // first == 2:
    print("O(n)")
elif second // first == 4:
    print("O(n^2)")