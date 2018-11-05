import math
# data amount
n = 12
tau = 0.0

fiY = 0.0
delA =0.0
delB =0.0

with open("fiz.txt", "r") as f:
	# get A, B coefficients 
	A,B = f.readline().split(',')

	A = float(A)
	B = float(B)
	# get measured values x,y 
	
	data = []
	for line in f:
		x,y = line.split('	')
		data.append( ( float(x),float(y) ) )
	
	# calculate tau
	v1 = 0.0
	v2 = 0.0
	for x,y in data:
		v1 += x**2
		v2 += x
	tau = (n*(v1)) - (v2**2)

	for x,y in data:
		fiY += (y - A*x -B)**2
	print("SUMA(epislon^2)=",fiY)

	fiY = math.sqrt(fiY/(n-2))

	delA = fiY*math.sqrt(n/tau)
	delB = fiY*math.sqrt(v1/tau)

	print("n =",n )
	print("tau=",tau )
	print("fiY=",fiY)
	print("v1=",v1)
	print("delA =", delA)
	print("delB =", delB)





	 