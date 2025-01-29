
with open("input.txt", "r") as file:
	data = file.read()

lines = data.splitlines()

arr1 = []
arr2 = []
for line in lines:
	words = line.split()
	arr1.append(int(words[0]))
	arr2.append(int(words[1]))

arr1.sort()
arr2.sort()

sum = 0
for i in range(len(arr1)):
	sum += abs(arr2[i] - arr1[i])

print("The sum of absolute differences is: ", sum)




