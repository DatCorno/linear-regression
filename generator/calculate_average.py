import subprocess
import sys

#benchmark the time taken for the data generation

number_of_execute = int(sys.argv[1])

sum = 0.0

for i in range(int(number_of_execute)):
	sum += float(subprocess.run(["./data_generator", "100000"], stdout=subprocess.PIPE).stdout.decode('utf-8'))

print((sum / number_of_execute))